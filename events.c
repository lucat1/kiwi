#include "events.h"
#include "config.h"
#include "data.h"
#include "kiwi.h"
#include "list.h"
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

    [XCB_FOCUS_IN] = handle_focus_in,
    [XCB_FOCUS_OUT] = handle_focus_out,

    [XCB_KEY_PRESS] = handle_key_press,
};

static uint32_t values[3];
static uint32_t min_x = WINDOW_MIN_X;
static uint32_t min_y = WINDOW_MIN_Y;

void handle_create_notify(xcb_generic_event_t *ev) {
  xcb_create_notify_event_t *e = (xcb_create_notify_event_t *)ev;
  client_t *c = new_client(e->window);
  list_append(&focdesk->clients, c);
  msg("added client to %p(%d), now at %d", focdesk, focdesk->i,
      list_size(focdesk->clients));
}

void handle_map_request(xcb_generic_event_t *ev) {
  xcb_map_request_event_t *e = (xcb_map_request_event_t *)ev;

#if !FOCUS_TYPE
  // start grabbing for clicks on the window
  xcb_grab_button(dpy, false, e->window, XCB_EVENT_MASK_BUTTON_PRESS,
                  XCB_GRAB_MODE_SYNC, XCB_GRAB_MODE_ASYNC, XCB_NONE, XCB_NONE,
                  XCB_BUTTON_INDEX_1, XCB_NONE);
#endif

  client_t *c = get_client(e->window);
  xcb_map_window(dpy, c->window);

  focdesk->layout.reposition(focdesk);
  setBorderWidth(c->window);
  values[0] = XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_FOCUS_CHANGE;
  xcb_change_window_attributes_checked(dpy, c->window, XCB_CW_EVENT_MASK,
                                       values);
  focus_client(c);
}

void handle_destroy_notify(xcb_generic_event_t *ev) {
  xcb_destroy_notify_event_t *e = (xcb_destroy_notify_event_t *)ev;
  client_t *c = get_client(e->window);

  // discard any window information
  xcb_ungrab_button(dpy, XCB_BUTTON_INDEX_1, c->window, XCB_NONE);
  xcb_kill_client(dpy, c->window);
  list_remove(&focdesk->clients, c);

  // focus the new best client
  stack_remove(&focdesk->focus_stack, c);
  if (focdesk->focus_stack != NULL)
    focus_client((client_t *)focdesk->focus_stack->value);
}

void handle_button_press(xcb_generic_event_t *ev) {
  xcb_button_press_event_t *e = (xcb_button_press_event_t *)ev;
  client_t *c = get_client(e->state < MODKEY ? e->event : e->child);
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

  values[0] = XCB_STACK_MODE_ABOVE;
  xcb_get_geometry_reply_t *geom = xcb_geometry(dpy, c->window);

  if (e->detail == 1) {
    c->motion = MOTION_RESIZING;
    xcb_warp_pointer(dpy, XCB_NONE, scr->root, 0, 0, 0, 0, geom->x, geom->y);
  } else {
    c->motion = MOTION_DRAGGING;
    xcb_warp_pointer(dpy, XCB_NONE, scr->root, 0, 0, 0, 0,
                     geom->x + geom->width, geom->y + geom->height);
  }
  free(geom);

  xcb_grab_pointer(dpy, false, scr->root,
                   XCB_EVENT_MASK_BUTTON_RELEASE |
                       XCB_EVENT_MASK_BUTTON_MOTION |
                       XCB_EVENT_MASK_POINTER_MOTION_HINT,
                   XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC, scr->root,
                   XCB_NONE, XCB_CURRENT_TIME);
}

void handle_motion_notify(xcb_generic_event_t *ev) {
  UNUSED(ev);
  client_t *c = focdesk->focused;
  xcb_query_pointer_cookie_t coord = xcb_query_pointer(dpy, scr->root);
  xcb_query_pointer_reply_t *poin = xcb_query_pointer_reply(dpy, coord, 0);
  if (c->motion == MOTION_RESIZING) {
    int16_t x =
        ((poin->root_x + c->w + (2 * BORDER_WIDTH)) > scr->width_in_pixels)
            ? (scr->width_in_pixels - c->w - (2 * BORDER_WIDTH))
            : poin->root_x;
    int16_t y =
        ((poin->root_y + c->h + (2 * BORDER_WIDTH)) > scr->height_in_pixels)
            ? (scr->height_in_pixels - c->h - (2 * BORDER_WIDTH))
            : poin->root_y;
    move_client(c, x, y);
  } else if (c->motion == MOTION_DRAGGING) {
    if (!((poin->root_x <= c->x) || (poin->root_y <= c->y))) {
      uint16_t width = poin->root_x - c->x - BORDER_WIDTH;
      uint16_t height = poin->root_y - c->y - BORDER_WIDTH;
      if (width >= min_x && height >= min_y) {
        resize_client(c, width, height);
      }
    }
  }
}

void handle_configure_notify(xcb_generic_event_t *ev) {
  xcb_configure_notify_event_t *e = (xcb_configure_notify_event_t *)ev;
  client_t *c = get_client(e->window);
  if (c == NULL || c->motion != MOTION_NONE)
    return;

  c->x = e->x;
  c->y = e->y;
  c->w = e->width;
  c->h = e->height;
}

void handle_button_release(xcb_generic_event_t *ev) {
  UNUSED(ev);
  if (focdesk->focused != NULL)
    focdesk->focused->motion = MOTION_NONE;

  xcb_ungrab_pointer(dpy, XCB_CURRENT_TIME);
}

#if FOCUS_TYPE
void handle_enter_notify(xcb_generic_event_t *ev) {
  xcb_enter_notify_event_t *e = (xcb_enter_notify_event_t *)ev;
  client_t *c = get_client(e->event);
  focus_client(c);
}
#endif // FOCUS_TYPE

void handle_focus_in(xcb_generic_event_t *ev) {
  xcb_focus_in_event_t *e = (xcb_focus_in_event_t *)ev;
  setBorderColor(e->event, 1);
}

void handle_focus_out(xcb_generic_event_t *ev) {
  xcb_focus_out_event_t *e = (xcb_focus_out_event_t *)ev;
  setBorderColor(e->event, 0);
}

void handle_key_press(xcb_generic_event_t *ev) {
  xcb_key_press_event_t *e = (xcb_key_press_event_t *)ev;
  client_t *c = get_client(e->child);
  focus_client(c);

  xcb_keysym_t keysym = xcb_get_keysym(dpy, e->detail);
  int key_table_size = sizeof(keys) / sizeof(*keys);
  for (int i = 0; i < key_table_size; ++i) {
    if ((keys[i].keysym == keysym) && (keys[i].mod == e->state)) {
      keys[i].func(keys[i].com);
    }
  }
}
