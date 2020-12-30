#include "events.h"
#include "config.h"
#include "data.h"
#include "kiwi.h"
#include "list.h"
#include "randr.h"
#include "util.h"
#include <stdbool.h>
#include <stdlib.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

void (*events[XCB_NO_OPERATION])(xcb_generic_event_t *e) = {
    [XCB_CREATE_NOTIFY] = handle_create_notify,
    [XCB_MAP_REQUEST] = handle_map_request,
    [XCB_DESTROY_NOTIFY] = handle_destroy_notify,

    [XCB_BUTTON_PRESS] = handle_button_press,
    [XCB_MOTION_NOTIFY] = handle_motion_notify,
    [XCB_CONFIGURE_NOTIFY] = handle_configure_notify,
    [XCB_BUTTON_RELEASE] = handle_button_release,

#if FOCUS_TYPE
    [XCB_ENTER_NOTIFY] = handle_enter_notify,
#endif // FOCUS_TYPE

    [XCB_KEY_PRESS] = handle_key_press,
};

void handle_create_notify(xcb_generic_event_t *ev) {
  xcb_create_notify_event_t *e = (xcb_create_notify_event_t *)ev;
  client_t *c = new_client(e->window);
  list_append(&focdesk->clients, c);
}

void handle_map_request(xcb_generic_event_t *ev) {
  xcb_map_request_event_t *e = (xcb_map_request_event_t *)ev;
  client_t *c = get_client(e->window);

#if !FOCUS_TYPE
  // start grabbing for clicks on the window
  xcb_grab_button(dpy, false, c->window, XCB_EVENT_MASK_BUTTON_PRESS,
                  XCB_GRAB_MODE_SYNC, XCB_GRAB_MODE_ASYNC, XCB_NONE, XCB_NONE,
                  XCB_BUTTON_INDEX_1, XCB_NONE);
#endif
  uint32_t values[1] = {(FOCUS_TYPE ? XCB_EVENT_MASK_ENTER_WINDOW : 0) |
                        XCB_EVENT_MASK_FOCUS_CHANGE};
  xcb_change_window_attributes_checked(dpy, c->window, XCB_CW_EVENT_MASK,
                                       values);

  c->mapped = true;
  show_client(c);
  border_width(c, BORDER_WIDTH);
  focus_client(c);
  focdesk->layout.reposition(focdesk);
}

void handle_destroy_notify(xcb_generic_event_t *ev) {
  xcb_destroy_notify_event_t *e = (xcb_destroy_notify_event_t *)ev;
  client_t *c = get_client(e->window);

  // discard any window information
  c->mapped = false;
  xcb_ungrab_button(dpy, XCB_BUTTON_INDEX_1, c->window, XCB_NONE);
  xcb_kill_client(dpy, c->window);

  list_remove(&focdesk->clients, c);
  stack_remove(&focdesk->focus_stack, c);
  if (focdesk->focused == c)
    focdesk->focused = NULL;

  // focus the new best client
  if (focdesk->focus_stack != NULL)
    focus_client((client_t *)focdesk->focus_stack->value);
  focdesk->layout.reposition(focdesk);
}

int16_t start_x, start_y;
void handle_button_press(xcb_generic_event_t *ev) {
  xcb_button_press_event_t *e = (xcb_button_press_event_t *)ev;
  client_t *c = get_client(e->state < MODKEY ? e->event : e->child);
  monitor_t *mon = get_monitor_by_coords(e->root_x, e->root_y);
  if (mon != NULL)
    focmon = mon;

#if DEBUG
  print_monitors();
#endif

  if (c == NULL || c->window == 0 || c->window == scr->root)
    return;

  focus_client(c);
  // propagate click events
  xcb_allow_events(dpy, XCB_ALLOW_REPLAY_POINTER, e->time);
  xcb_flush(dpy);

  // stop if we're not holding a mod key as we're just
  // clicking to focus
  if (e->state < MODKEY) {
    return;
  }

  start_x = e->root_x;
  start_y = e->root_y;
  if (e->detail == 1)
    c->motion = MOTION_DRAGGING;
  else
    c->motion = MOTION_RESIZING;

  xcb_grab_pointer(dpy, false, scr->root,
                   XCB_EVENT_MASK_BUTTON_RELEASE |
                       XCB_EVENT_MASK_BUTTON_MOTION |
                       XCB_EVENT_MASK_POINTER_MOTION_HINT,
                   XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC, scr->root,
                   XCB_NONE, XCB_CURRENT_TIME);
}

void handle_motion_notify(xcb_generic_event_t *ev) {
  UNUSED(ev);
  xcb_query_pointer_cookie_t coord = xcb_query_pointer(dpy, scr->root);
  xcb_query_pointer_reply_t *pointer = xcb_query_pointer_reply(dpy, coord, 0);
  rel_pointer_t *p = malloc(sizeof(rel_pointer_t));
  p->x = pointer->root_x - start_x;
  p->y = pointer->root_y - start_y;
  free(pointer);
  focdesk->layout.motion(p, focdesk->focused, focmon);
  free(p);
}

void handle_configure_notify(xcb_generic_event_t *ev) {
  xcb_configure_notify_event_t *e = (xcb_configure_notify_event_t *)ev;
  if (e->window == 0 || e->window == scr->root) {
    // if the dimentions have changed update the root window sizes
    if (e->width != scr->width_in_pixels ||
        e->height != scr->height_in_pixels) {
      scr->width_in_pixels = e->width;
      scr->height_in_pixels = e->height;

      if (randr_base != -1) {
        get_randr();
        for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
          desktop_t *desk = ((monitor_t *)miter->value)->focused;
          if (desk != NULL)
            desk->layout.reposition(desk);
        }
      }
    }
  } else {
    client_t *c = get_client(e->window);
    if (c == NULL || c->motion != MOTION_NONE || c->visibility == HIDDEN)
      return;

    c->x = e->x;
    c->y = e->y;
    c->w = e->width;
    c->h = e->height;
  }
}

void handle_button_release(xcb_generic_event_t *ev) {
  UNUSED(ev);
  if (focdesk->focused != NULL) {
    focdesk->focused->motion = MOTION_NONE;
    save_client(focdesk->focused, focdesk->layout.type);
  }

  xcb_ungrab_pointer(dpy, XCB_CURRENT_TIME);
}

#if FOCUS_TYPE
void handle_enter_notify(xcb_generic_event_t *ev) {
  xcb_enter_notify_event_t *e = (xcb_enter_notify_event_t *)ev;
  client_t *c = get_client(e->event);
  focus_client(c);
}
#endif // FOCUS_TYPE

void handle_key_press(xcb_generic_event_t *ev) {
  xcb_key_press_event_t *e = (xcb_key_press_event_t *)ev;
  xcb_keysym_t keysym = xcb_get_keysym(dpy, e->detail);
  int key_table_size = sizeof(keys) / sizeof(*keys);

  for (int i = 0; i < key_table_size; ++i) {
    if ((keys[i].keysym == keysym) && (keys[i].mod == e->state)) {
      keys[i].func(keys[i].arg);
    }
  }
}
