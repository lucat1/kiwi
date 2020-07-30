#include <stdio.h>
#include <stdlib.h>

#include <xcb/xcb.h>

#include "kiwi.h"

static void subscribe(xcb_window_t w);

static void handle_xerror(xcb_generic_event_t *ev);
static void handle_button(xcb_generic_event_t *ev);
static void handle_map_notify(xcb_generic_event_t *ev);

xcb_connection_t *conn;
xcb_screen_t *scr;

static void (*events[XCB_NO_OPERATION])(xcb_generic_event_t *e) = {
    [0] = handle_xerror,
    [XCB_BUTTON_PRESS] = handle_button,
    [XCB_MAP_NOTIFY] = handle_map_notify,
};

// subscribe to a subwindow's events
static void subscribe(xcb_window_t win) {
  msg("subscribing to window %i", win);
  xcb_grab_button(conn, false, win, XCB_EVENT_MASK_BUTTON_PRESS,
                  XCB_GRAB_MODE_SYNC, XCB_GRAB_MODE_ASYNC, XCB_WINDOW_NONE,
                  XCB_CURSOR_NONE, XCB_BUTTON_INDEX_ANY, XCB_BUTTON_MASK_ANY);
}

static void handle_xerror(xcb_generic_event_t *ev) {
  // from: https://github.com/kaugm/mmwm/blob/master/mmwm.c#L2828
  xcb_generic_error_t *error = (xcb_generic_error_t *)ev;
  msg("recieved X11 error: %i, %i:%i [%i]\n", error->error_code,
      (int)error->major_code, (int)error->minor_code, (int)error->resource_id);
}

static void handle_button(xcb_generic_event_t *ev) {
  xcb_button_press_event_t *e;
  e = (xcb_button_press_event_t *)ev;

  msg("button %i pressed", e->detail);

  // propagate the button clicks
  xcb_allow_events(conn, XCB_ALLOW_REPLAY_POINTER, e->time);
  xcb_flush(conn);
}

static void handle_map_notify(xcb_generic_event_t *ev) {
  xcb_create_notify_event_t *e;
  e = (xcb_create_notify_event_t *)ev;
  msg("displaying window %i", e->window);

  subscribe(e->window);
}

static void clean() {
  if (conn != NULL)
    xcb_disconnect(conn);
}

static void setup() {
  scr = xcb_setup_roots_iterator(xcb_get_setup(conn)).data;

  // recieve updates on newly created windows
  static const uint32_t values[] = {XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY};
  xcb_change_window_attributes_checked(conn, scr->root, XCB_CW_EVENT_MASK,
                                       values);
}

static void loop() {
  uint8_t type;
  xcb_generic_event_t *ev;

  for (;;) {
    xcb_flush(conn);
    if (xcb_connection_has_error(conn))
      die("X11 connection error");

    if ((ev = xcb_wait_for_event(conn)) != NULL) {
      type = CLEANMASK(ev->response_type);

      if (events[type])
        events[type](ev);
      else
        msg("unhandled event: %s", xcb_event_str(ev));

      free(ev);
    }
  }
}

int main() {
  atexit(clean);

  if (xcb_connection_has_error(conn = xcb_connect(NULL, NULL)))
    die("Could not open connection to the X server");

  // load configuration files and grab root window events
  setup();

  loop();

  return 1;
}
