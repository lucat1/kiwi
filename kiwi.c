#include <stdio.h>
#include <stdlib.h>

#include <xcb/xcb.h>

#include "client.h"
#include "config.h"
#include "desktop.h"
#include "kiwi.h"
#include "util.h"
#include "vec.h"

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

static void handle_xerror(xcb_generic_event_t *ev) {
  // from: https://github.com/kaugm/mmwm/blob/master/mmwm.c#L2828
  xcb_generic_error_t *error = (xcb_generic_error_t *)ev;
  msg("recieved X11 error: %i, %i:%i [%i]\n", error->error_code,
      (int)error->major_code, (int)error->minor_code, (int)error->resource_id);
}

static void handle_button(xcb_generic_event_t *ev) {
  size_t i;
  xcb_button_press_event_t *e;
  client_t *c;

  e = (xcb_button_press_event_t *)ev;
  if ((c = client_from_window(e->event)) == NULL) {
    warn("button click on unmanaged window");
    return;
  }

  // focus the window on left click
  if (desktop_curr->focus != c)
    for (i = 0; i < vec_size(config.mouse_focus); i++)
      if (e->detail == config.mouse_focus[i])
        client_focus(c);

  msg("button %i pressed", e->detail);

  // propagate the button clicks
  xcb_allow_events(conn, XCB_ALLOW_REPLAY_POINTER, e->time);
  xcb_flush(conn);

  // grab the button if the user is about to resize the window
}

static void handle_map_notify(xcb_generic_event_t *ev) {
  xcb_create_notify_event_t *e;
  e = (xcb_create_notify_event_t *)ev;
  msg("displaying window %i", e->window);

  if (client_from_window(e->window) != NULL) {
    warn("tried to rehandle existing window as a client");
    return;
  }

  client_create(e->window);
}

static void clean() {
  if (config.mouse_focus != NULL)
    free(config.mouse_focus);

  if (clients != NULL)
    free(clients);

  if (desktops != NULL)
    free(desktops);

  if (conn != NULL)
    xcb_disconnect(conn);
}

static void setup() {
  size_t i;
  vec_t(int) mouse_focus;

  scr = xcb_setup_roots_iterator(xcb_get_setup(conn)).data;

  // recieve updates on newly created windows
  static const uint32_t values[] = {XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY};
  xcb_change_window_attributes_checked(conn, scr->root, XCB_CW_EVENT_MASK,
                                       values);

  // setup the default configuration
  for (i = 0; i < sizeof(default_mouse_focus) / sizeof(int); i++)
    vec_push(mouse_focus, default_mouse_focus[i]);

  config.mouse_focus = mouse_focus;
}

static void loop() {
  uint8_t type;
  xcb_generic_event_t *ev;

  for (;;) {
    xcb_flush(conn);
    if (xcb_connection_has_error(conn))
      die("X11 connection error");

    // some may say it's better to use `xcb_poll_for_event`.
    // polling should have worse performance, but may be snappier idk.
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
