#include "kiwi.h"
#include "config.h"
#include "data.h"
#include "events.h"
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

desktop_t *desktops = NULL;
desktop_t *focdesk = NULL;
xcb_connection_t *dpy = NULL;
xcb_screen_t *scr = NULL;

void killclient(char **com) {
  UNUSED(com);
  if (focdesk->focused != NULL)
    xcb_kill_client(dpy, focdesk->focused->window);
}

void closewm(char **com) {
  UNUSED(com);
  if (dpy != NULL) {
    xcb_disconnect(dpy);
  }
}

void spawn(char **com) {
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

void focus_client(client_t *c) {
  if (c == NULL)
    return;

  if (c->window != 0 && c->window != scr->root) {
    xcb_set_input_focus(dpy, XCB_INPUT_FOCUS_POINTER_ROOT, c->window,
                        XCB_CURRENT_TIME);

    // set the focused client value
    focdesk->focused = c;
    // push the client to the focus list if we have an empty one or
    // the client isn't already at the top of it
    if ((focdesk->focus_stack != NULL && focdesk->focus_stack->value != c) ||
        focdesk->focus_stack == NULL)
      stack_push(&focdesk->focus_stack, c);

    // move the focused window above all others
    static const uint32_t v[] = {XCB_STACK_MODE_ABOVE};
    xcb_configure_window(dpy, c->window, XCB_CONFIG_WINDOW_STACK_MODE, v);
    xcb_flush(dpy);
  }
}

void setBorderColor(xcb_window_t window, int focus) {
  if ((BORDER_WIDTH > 0) && (scr->root != window) && (0 != window)) {
    uint32_t vals[1];
    vals[0] = focus ? BORDER_COLOR_FOCUSED : BORDER_COLOR_UNFOCUSED;
    xcb_change_window_attributes(dpy, window, XCB_CW_BORDER_PIXEL, vals);
    xcb_flush(dpy);
  }
}

void setBorderWidth(xcb_window_t window) {
  if ((BORDER_WIDTH > 0) && (scr->root != window) && (0 != window)) {
    uint32_t vals[2];
    vals[0] = BORDER_WIDTH;
    xcb_configure_window(dpy, window, XCB_CONFIG_WINDOW_BORDER_WIDTH, vals);
    xcb_flush(dpy);
  }
}

static void setup() {
  xcb_keycode_t *keycode;
  // subscribe to events on the root window
  uint32_t values[] = {ROOT_EVENT_MASK};
  xcb_change_window_attributes(dpy, scr->root, XCB_CW_EVENT_MASK, values);

  // grab keys
  xcb_ungrab_key(dpy, XCB_GRAB_ANY, scr->root, XCB_MOD_MASK_ANY);
  for (int i = 0; i < SIZEOF(keys); ++i) {
    keycode = xcb_get_keycode(dpy, keys[i].keysym);
    if (keycode != NULL) {
      xcb_grab_key(dpy, true, scr->root, keys[i].mod, *keycode,
                   XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC);
      free(keycode);
    }
  }

  // grab buttons
#define GRAB(b)                                                                \
  xcb_grab_button(dpy, false, scr->root,                                       \
                  XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE, \
                  XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC, scr->root,         \
                  XCB_NONE, b, MODKEY);
  GRAB(XCB_BUTTON_INDEX_1);
  GRAB(XCB_BUTTON_INDEX_3);
#undef GRAB

  xcb_flush(dpy);

  // setup the first desktop
  desktops = focdesk = new_desktop(DEFAULT_LAYOUT);
}

void clean() {
  desktop_t *iter = desktops;
  while (iter != NULL) {
    free_clients(iter->clients);
    iter = iter->next;
  }

  free_desktops(desktops);
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
      int type = ev->response_type & ~0x80;
      if (events[type])
        events[type](ev);
#ifdef DEBUG
      else
        msg("unhandled event: %s", xcb_event_str(type));
#endif // DEBUG
      free(ev);
    }

    if (xcb_has_error(dpy))
      running = false;
  }

  clean();
}
