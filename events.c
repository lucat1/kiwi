#include "events.h"
#include "config.h"
#include "data.h"
#include "kiwi.h"
#include "util.h"
#include <stdbool.h>
#include <stdlib.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

void (*events[XCB_NO_OPERATION])(xcb_generic_event_t *e) = {
    [XCB_MAP_REQUEST] = handle_map_request,
    [XCB_DESTROY_NOTIFY] = handle_destroy_notify,

    [XCB_BUTTON_PRESS] = handle_button_press,
    [XCB_MOTION_NOTIFY] = handle_motion_notify,
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

void handle_map_request(xcb_generic_event_t *ev) {
  xcb_map_request_event_t *e = (xcb_map_request_event_t *)ev;

#if !FOCUS_TYPE
  // start grabbing for clicks on the window
  xcb_grab_button(dpy, false, e->window, XCB_EVENT_MASK_BUTTON_PRESS,
                  XCB_GRAB_MODE_SYNC, XCB_GRAB_MODE_ASYNC, XCB_NONE, XCB_NONE,
                  XCB_BUTTON_INDEX_1, XCB_NONE);
#endif

  client_t *c = new_client(e->window);
  focused_desktop->clients = push_client(focused_desktop->clients, c);
  xcb_map_window(dpy, c->window);

  focused_desktop->layout.reposition(focused_desktop);
  setBorderWidth(c->window);
  values[0] = XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_FOCUS_CHANGE;
  xcb_change_window_attributes_checked(dpy, c->window, XCB_CW_EVENT_MASK,
                                       values);
  setFocus(e->window);
}

void handle_destroy_notify(xcb_generic_event_t *ev) {
  xcb_destroy_notify_event_t *e = (xcb_destroy_notify_event_t *)ev;
  xcb_ungrab_button(dpy, XCB_BUTTON_INDEX_1, e->window, XCB_NONE);
  xcb_kill_client(dpy, e->window);
}

void handle_button_press(xcb_generic_event_t *ev) {
  xcb_button_press_event_t *e = (xcb_button_press_event_t *)ev;
  int wid = e->state < MODKEY ? e->event : e->child;
  setFocus(wid);

  // propagate click events
  xcb_allow_events(dpy, XCB_ALLOW_REPLAY_POINTER, e->time);
  xcb_flush(dpy);

  if (e->state < MODKEY || wid == 0) {
    return;
  }

  values[0] = XCB_STACK_MODE_ABOVE;
  xcb_get_geometry_reply_t *geom = xcb_geometry(dpy, focused);

  if (e->detail == 1) {
    values[2] = 1;
    xcb_warp_pointer(dpy, XCB_NONE, scr->root, 0, 0, 0, 0, geom->x, geom->y);
  } else if (focused != 0) {
    values[2] = 3;
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
  xcb_query_pointer_cookie_t coord = xcb_query_pointer(dpy, scr->root);
  xcb_query_pointer_reply_t *poin = xcb_query_pointer_reply(dpy, coord, 0);
  uint32_t val[2] = {1, 3};
  if ((values[2] == val[0]) && (focused != 0)) {
    xcb_get_geometry_cookie_t geom_now = xcb_get_geometry(dpy, focused);
    xcb_get_geometry_reply_t *geom =
        xcb_get_geometry_reply(dpy, geom_now, NULL);
    values[0] = ((poin->root_x + geom->width + (2 * BORDER_WIDTH)) >
                 scr->width_in_pixels)
                    ? (scr->width_in_pixels - geom->width - (2 * BORDER_WIDTH))
                    : poin->root_x;
    values[1] =
        ((poin->root_y + geom->height + (2 * BORDER_WIDTH)) >
         scr->height_in_pixels)
            ? (scr->height_in_pixels - geom->height - (2 * BORDER_WIDTH))
            : poin->root_y;
    xcb_configure_window(dpy, focused,
                         XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, values);
  } else if ((values[2] == val[1]) && (focused != 0)) {
    xcb_get_geometry_cookie_t geom_now = xcb_get_geometry(dpy, focused);
    xcb_get_geometry_reply_t *geom =
        xcb_get_geometry_reply(dpy, geom_now, NULL);
    if (!((poin->root_x <= geom->x) || (poin->root_y <= geom->y))) {
      values[0] = poin->root_x - geom->x - BORDER_WIDTH;
      values[1] = poin->root_y - geom->y - BORDER_WIDTH;
      if ((values[0] >= min_x) && (values[1] >= min_y)) {
        xcb_configure_window(dpy, focused,
                             XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                             values);
      }
    }
  }
}

void handle_button_release(xcb_generic_event_t *ev) {
  UNUSED(ev);
  xcb_ungrab_pointer(dpy, XCB_CURRENT_TIME);
}

#if FOCUS_TYPE
void handle_enter_notify(xcb_generic_event_t *ev) {
  xcb_enter_notify_event_t *e = (xcb_enter_notify_event_t *)ev;
  setFocus(e->event);
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
  xcb_keysym_t keysym = xcb_get_keysym(dpy, e->detail);
  focused = e->child;
  int key_table_size = sizeof(keys) / sizeof(*keys);
  for (int i = 0; i < key_table_size; ++i) {
    if ((keys[i].keysym == keysym) && (keys[i].mod == e->state)) {
      keys[i].func(keys[i].com);
    }
  }
}
