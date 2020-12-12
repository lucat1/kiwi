#include "kiwi.h"
#include "config.h"
#include "data.h"
#include "util.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <xcb/xcb.h>

#define ROOT_EVENT_MASK                                                        \
  (XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | \
   XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_BUTTON_PRESS)
#define UNUSED(x) (void)(x)

static desktop_t kiwi_desktops[desktops];

static xcb_connection_t *dpy; // the X display
static xcb_screen_t *scr;

// below is stuff to refactor
static xcb_window_t win, focused;
static uint32_t values[3];
static uint32_t min_x = WINDOW_MIN_X;
static uint32_t min_y = WINDOW_MIN_Y;

static void killclient(char **com) {
  UNUSED(com);
  xcb_kill_client(dpy, focused);
}

static void closewm(char **com) {
  UNUSED(com);
  if (dpy != NULL) {
    xcb_disconnect(dpy);
  }
}

static void spawn(char **com) {
  if (fork() == 0) {
    if (dpy != NULL) {
      close(scr->root);
    }
    setsid();
    if (fork() != 0) {
      exit(0);
    }
    execvp((char *)com[0], (char **)com);
    exit(0);
  }
  wait(NULL);
}

static void handleButtonPress(xcb_generic_event_t *ev) {
  xcb_button_press_event_t *e = (xcb_button_press_event_t *)ev;
  win = e->child;
  setFocus(e->event);

  xcb_allow_events(dpy, XCB_ALLOW_REPLAY_POINTER, e->time);
  xcb_flush(dpy);

  if (e->state < MODKEY) {
    return;
  }

  values[0] = XCB_STACK_MODE_ABOVE;
  xcb_get_geometry_cookie_t geom_now = xcb_get_geometry(dpy, win);
  xcb_get_geometry_reply_t *geom = xcb_get_geometry_reply(dpy, geom_now, NULL);
  if (1 == e->detail) {
    values[2] = 1;
    xcb_warp_pointer(dpy, XCB_NONE, win, 0, 0, 0, 0, 1, 1);
  } else if (win != 0) {
    values[2] = 3;
    xcb_warp_pointer(dpy, XCB_NONE, win, 0, 0, 0, 0, geom->width, geom->height);
  }

  xcb_grab_pointer(dpy, 0, scr->root,
                   XCB_EVENT_MASK_BUTTON_RELEASE |
                       XCB_EVENT_MASK_BUTTON_MOTION |
                       XCB_EVENT_MASK_POINTER_MOTION_HINT,
                   XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC, scr->root,
                   XCB_NONE, XCB_CURRENT_TIME);
}

static void handleMotionNotify(xcb_generic_event_t *ev) {
  UNUSED(ev);
  xcb_query_pointer_cookie_t coord = xcb_query_pointer(dpy, scr->root);
  xcb_query_pointer_reply_t *poin = xcb_query_pointer_reply(dpy, coord, 0);
  uint32_t val[2] = {1, 3};
  if ((values[2] == val[0]) && (win != 0)) {
    xcb_get_geometry_cookie_t geom_now = xcb_get_geometry(dpy, win);
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
    xcb_configure_window(dpy, win, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y,
                         values);
  } else if ((values[2] == val[1]) && (win != 0)) {
    xcb_get_geometry_cookie_t geom_now = xcb_get_geometry(dpy, win);
    xcb_get_geometry_reply_t *geom =
        xcb_get_geometry_reply(dpy, geom_now, NULL);
    if (!((poin->root_x <= geom->x) || (poin->root_y <= geom->y))) {
      values[0] = poin->root_x - geom->x - BORDER_WIDTH;
      values[1] = poin->root_y - geom->y - BORDER_WIDTH;
      if ((values[0] >= min_x) && (values[1] >= min_y)) {
        xcb_configure_window(dpy, win,
                             XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                             values);
      }
    }
  }
}

static void setFocus(xcb_drawable_t window) {
  if ((window != 0) && (window != scr->root)) {
    xcb_set_input_focus(dpy, XCB_INPUT_FOCUS_POINTER_ROOT, window,
                        XCB_CURRENT_TIME);
    focused = window;

    // move the focused window above all others
    static const uint32_t v[] = {XCB_STACK_MODE_ABOVE};
    xcb_configure_window(dpy, window, XCB_CONFIG_WINDOW_STACK_MODE, v);
    xcb_flush(dpy);
  }
}

static void setBorderColor(xcb_window_t window, int focus) {
  if ((BORDER_WIDTH > 0) && (scr->root != window) && (0 != window)) {
    uint32_t vals[1];
    vals[0] = focus ? BORDER_COLOR_FOCUSED : BORDER_COLOR_UNFOCUSED;
    xcb_change_window_attributes(dpy, window, XCB_CW_BORDER_PIXEL, vals);
    xcb_flush(dpy);
  }
}

static void setBorderWidth(xcb_window_t window) {
  if ((BORDER_WIDTH > 0) && (scr->root != window) && (0 != window)) {
    uint32_t vals[2];
    vals[0] = BORDER_WIDTH;
    xcb_configure_window(dpy, window, XCB_CONFIG_WINDOW_BORDER_WIDTH, vals);
    xcb_flush(dpy);
  }
}

static void setWindowDimensions(xcb_window_t window) {
  if ((scr->root != window) && (0 != window)) {
    uint32_t vals[2];
    vals[0] = WINDOW_X;
    vals[1] = WINDOW_Y;
    xcb_configure_window(
        dpy, window, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, vals);
    xcb_flush(dpy);
  }
}

static void setWindowPosition(xcb_window_t window) {
  if ((scr->root != window) && (0 != window)) {
    uint32_t vals[2];
    vals[0] = (scr->width_in_pixels / 2) - (WINDOW_X / 2);
    vals[1] = (scr->height_in_pixels / 2) - (WINDOW_Y / 2);
    xcb_configure_window(dpy, window, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y,
                         vals);
    xcb_flush(dpy);
  }
}

static void handleKeyPress(xcb_generic_event_t *ev) {
  xcb_key_press_event_t *e = (xcb_key_press_event_t *)ev;
  xcb_keysym_t keysym = xcb_get_keysym(dpy, e->detail);
  win = e->child;
  int key_table_size = sizeof(keys) / sizeof(*keys);
  for (int i = 0; i < key_table_size; ++i) {
    if ((keys[i].keysym == keysym) && (keys[i].mod == e->state)) {
      keys[i].func(keys[i].com);
    }
  }
}

static void handleEnterNotify(xcb_generic_event_t *ev) { UNUSED(ev); }

static void handleLeaveNotify(xcb_generic_event_t *ev) { UNUSED(ev); }

static void handleButtonRelease(xcb_generic_event_t *ev) {
  UNUSED(ev);
  xcb_ungrab_pointer(dpy, XCB_CURRENT_TIME);
}

static void handleDestroyNotify(xcb_generic_event_t *ev) {
  xcb_destroy_notify_event_t *e = (xcb_destroy_notify_event_t *)ev;
  xcb_ungrab_button(dpy, XCB_BUTTON_INDEX_1, e->window, XCB_NONE);
  xcb_kill_client(dpy, e->window);
}

static void handleFocusIn(xcb_generic_event_t *ev) {
  xcb_focus_in_event_t *e = (xcb_focus_in_event_t *)ev;
  setBorderColor(e->event, 1);
}

static void handleFocusOut(xcb_generic_event_t *ev) {
  xcb_focus_out_event_t *e = (xcb_focus_out_event_t *)ev;
  setBorderColor(e->event, 0);
}

static void handleMapRequest(xcb_generic_event_t *ev) {
  xcb_map_request_event_t *e = (xcb_map_request_event_t *)ev;
  xcb_grab_button(dpy, false, e->window, XCB_EVENT_MASK_BUTTON_PRESS,
                  XCB_GRAB_MODE_SYNC, XCB_GRAB_MODE_ASYNC, XCB_NONE, XCB_NONE,
                  XCB_BUTTON_INDEX_1, XCB_NONE);
  xcb_map_window(dpy, e->window);
  setWindowDimensions(e->window);
  setWindowPosition(e->window);
  setBorderWidth(e->window);
  values[0] = XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_FOCUS_CHANGE;
  xcb_change_window_attributes_checked(dpy, e->window, XCB_CW_EVENT_MASK,
                                       values);
  setFocus(e->window);
}

static void eventHandler(xcb_generic_event_t *ev) {
  handler_func_t *handler;
  for (handler = handler_funs; handler->func != NULL; handler++) {
    if ((ev->response_type & ~0x80) == handler->request) {
      handler->func(ev);
    }
  }
}

static void setup() {
  xcb_keycode_t *keycode;
  // subscribe to events on the root window
  uint32_t values[] = {ROOT_EVENT_MASK};
  xcb_change_window_attributes(dpy, scr->root, XCB_CW_EVENT_MASK, values);

  // grab keys as defined in the config
  xcb_ungrab_key(dpy, XCB_GRAB_ANY, scr->root, XCB_MOD_MASK_ANY);
  for (int i = 0; i < SIZEOF(keys); ++i) {
    keycode = xcb_get_keycode(dpy, keys[i].keysym);
    if (keycode != NULL) {
      xcb_grab_key(dpy, true, scr->root, keys[i].mod, *keycode,
                   XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC);
      free(keycode);
    }
  }

  /* grab buttons */
#define GRAB(b)                                                                \
  xcb_grab_button(dpy, false, scr->root,                                       \
                  XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE, \
                  XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC, scr->root,         \
                  XCB_NONE, b, MODKEY);
  GRAB(XCB_BUTTON_INDEX_1);
  GRAB(XCB_BUTTON_INDEX_3);
#undef GRAB

  xcb_flush(dpy);
}

int main() {
  dpy = xcb_connect(NULL, NULL);
  if (xcb_has_error(dpy))
    return 1;

  scr = xcb_setup_roots_iterator(xcb_get_setup(dpy)).data;
  setup();
  if (xcb_has_error(dpy))
    return 1;

  bool running = true;
  while (running) {
    xcb_flush(dpy);
    xcb_generic_event_t *ev;

    if ((ev = xcb_wait_for_event(dpy)) != NULL) {
      eventHandler(ev);
      free(ev);
    }

    if (xcb_has_error(dpy))
      running = false;
  }
}
