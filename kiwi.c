#include <stdio.h>
#include <stdlib.h>

#include <xcb/xcb.h>

#include "client.h"
#include "config.h"
#include "desktop.h"
#include "kiwi.h"
#include "util.h"
#include "vec.h"

static void handle(xcb_generic_event_t *ev);

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
  xcb_query_pointer_reply_t *pointer;
  xcb_grab_pointer_reply_t *grab_reply;
  client_t *client;
  int mx, my, xw, yh;

  e = (xcb_button_press_event_t *)ev;
  if ((client = client_from_window(e->event)) == NULL) {
    warn("button click on unmanaged window");
    return;
  }

  // focus the window when perssing the configured button
  if (desktop_curr->focus != client)
    for (i = 0; i < vec_size(config.mouse_focus); i++)
      if (e->detail == config.mouse_focus[i])
        client_focus(client);

  msg("button %i pressed", e->detail);

  pointer =
      xcb_query_pointer_reply(conn, xcb_query_pointer(conn, scr->root), 0);
  if (!pointer)
    return;
  mx = pointer->root_x;
  my = pointer->root_y;

  // grab the button if the user is about to resize the window
  msg("grabbing buttons");
  grab_reply = xcb_grab_pointer_reply(
      conn,
      xcb_grab_pointer(
          conn, false, scr->root,
          XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
              XCB_EVENT_MASK_BUTTON_MOTION | XCB_EVENT_MASK_POINTER_MOTION,
          XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC, XCB_NONE, XCB_NONE,
          XCB_CURRENT_TIME),
      NULL);

  if (!grab_reply || grab_reply->status != XCB_GRAB_STATUS_SUCCESS) {
    warn("could not grab pointer");
    free(grab_reply);
    free(pointer);
    return;
  } else {
    free(grab_reply);
  }

  xcb_generic_event_t *_e = NULL;
  xcb_motion_notify_event_t *_ev = NULL;
  int ungrab = false;
  while (!ungrab) {
    xcb_flush(conn);
    while (!(_e = xcb_wait_for_event(conn)))
      xcb_flush(conn);

    msg("got event %s", xcb_event_str(_e));

    switch (CLEANMASK(_e->response_type)) {
    case XCB_MOTION_NOTIFY:
      _ev = (xcb_motion_notify_event_t *)_e;
      // TODO: configurable key to move/resize
      xw = (_ev->detail == XCB_BUTTON_INDEX_1 ? client->x : client->width) +
           _ev->root_x - mx;
      yh = (_ev->detail == XCB_BUTTON_INDEX_1 ? client->y : client->height) +
           _ev->root_y - my;
      if (_ev->detail == XCB_BUTTON_INDEX_3)
        // TODO: min size
        client_resize(client, xw > 0 /*MINWSZ*/ ? xw : client->width,
                      yh > 0 /*MINWSZ*/ ? yh : client->height);
      else if (_ev->detail == XCB_BUTTON_INDEX_1)
        client_move(client, xw, yh);

      xcb_flush(conn);
      break;
    case XCB_KEY_PRESS:
    case XCB_KEY_RELEASE:
    case XCB_BUTTON_PRESS:
    case XCB_BUTTON_RELEASE:
      ungrab = true;
      break;

    default:
      handle(_e);
      break;
    }

    if (_e)
      free(_e);
  }
  msg("ungrabbing buttons");
  xcb_ungrab_pointer(conn, XCB_CURRENT_TIME);

  free(pointer);

  // propagate the button clicks
  msg("got here");
  xcb_allow_events(conn, XCB_ALLOW_REPLAY_POINTER, e->time);
  xcb_flush(conn);
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
    vec_free(config.mouse_focus);

  if (clients != NULL)
    vec_free(clients);

  if (desktops != NULL)
    vec_free(desktops);

  if (conn != NULL)
    xcb_disconnect(conn);
}

static void setup() {
  size_t i;
  vec_t(int) mouse_focus = NULL;

  scr = xcb_setup_roots_iterator(xcb_get_setup(conn)).data;

  // recieve updates on newly created windows
  static const uint32_t values[] = {XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY};
  xcb_change_window_attributes_checked(conn, scr->root, XCB_CW_EVENT_MASK,
                                       values);

  // setup the default configuration
  for (i = 0; i < sizeof(default_mouse_focus) / sizeof(int); i++) {
    if (default_mouse_focus[i] == 0)
      break;

    vec_push(mouse_focus, default_mouse_focus[i]);
  }
  config.mouse_focus = mouse_focus;

  // setup the requested number of desktops
  for (i = 0; i < (size_t)config.desktops; i++)
    desktop_add();
}

static void handle(xcb_generic_event_t *ev) {
  uint8_t type;
  type = CLEANMASK(ev->response_type);

  if (events[type])
    events[type](ev);
  else
    msg("unhandled event: %s", xcb_event_str(ev));
}

static void loop() {
  xcb_generic_event_t *ev;

  for (;;) {
    xcb_flush(conn);
    if (xcb_connection_has_error(conn))
      die("X11 connection error");

    // some may say it's better to use `xcb_poll_for_event`.
    // polling should have worse performance, but may be snappier idk.
    if ((ev = xcb_wait_for_event(conn)) != NULL) {
      handle(ev);
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
