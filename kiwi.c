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

list_t *desktops = NULL;
desktop_t *focdesk = NULL;
xcb_connection_t *dpy = NULL;
xcb_screen_t *scr = NULL;

void killclient(FN_ARG arg) {
  UNUSED(arg);
  if (focdesk->focused != NULL)
    xcb_kill_client(dpy, focdesk->focused->window);
}

void closewm(FN_ARG arg) {
  UNUSED(arg);
  if (dpy != NULL) {
    xcb_disconnect(dpy);
  }
}

void spawn(FN_ARG arg) {
  if (fork() == 0) {
    if (dpy != NULL) {
      close(scr->root);
    }
    setsid();
    if (fork() != 0) {
      exit(0);
    }
    execvp((char *)arg.v[0], (char **)arg.v);
    exit(0);
  }
  wait(NULL);
}

void send_to(FN_ARG arg) { send_client(focdesk->focused, arg.i); }
void send_rel(FN_ARG arg) { send_client(focdesk->focused, focdesk->i + arg.i); }

void move_to(FN_ARG arg) {
  desktop_t *desk = get_desktop(arg.i);
  if (desk != NULL)
    focus_desktop(desk);
}
void move_rel(FN_ARG arg) {
  FN_ARG a = {.i = focdesk->i + arg.i};
  move_to(a);
}

void focus_client(client_t *c) {
  if (c == NULL || (c->window == 0 && c->window == scr->root))
    return;

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
  xcb_set_input_focus(dpy, XCB_INPUT_FOCUS_POINTER_ROOT, c->window,
                      XCB_CURRENT_TIME);
  xcb_flush(dpy);
}

void move_client(client_t *c, int16_t x, int16_t y, bool save) {
  if (c == NULL)
    return;

  if (save) {
    c->x = x;
    c->y = y;
  }
  uint32_t values[2] = {x, y};
  xcb_configure_window(dpy, c->window,
                       XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, values);
}

void resize_client(client_t *c, uint16_t width, uint16_t height) {
  if (c == NULL)
    return;

  c->w = width;
  c->h = height;
  uint32_t values[2] = {width, height};
  xcb_configure_window(dpy, c->window,
                       XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                       values);
}

void move_resize_client(client_t *c, int16_t x, int16_t y, uint16_t width,
                        uint16_t height) {
  if (c == NULL)
    return;

  c->x = x;
  c->y = y;
  c->w = width;
  c->h = height;
  uint32_t values[4] = {x, y, width, height};
  xcb_configure_window(dpy, c->window,
                       XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y |
                           XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                       values);
}

void hide_client(client_t *c) {
  c->visibility = HIDDEN;
  move_client(c, scr->width_in_pixels, scr->height_in_pixels, false);
}

void show_client(client_t *c) {
  c->visibility = SHOWN;
  move_client(c, c->x, c->y, false);
}

void send_client(client_t *c, int i) {
  if (i < 0 || c == NULL)
    return;

  desktop_t *desk = get_desktop(i);
  if (desk == NULL)
#if CREATE_DESKTOP_IF_NOT_EXISTS
    while (list_size(desktops) <= i) {
      desk = new_desktop(DEFAULT_LAYOUT);
      list_append(&desktops, desk);
    }
#else
    return;
#endif

  // remove it from the old workspace and refocus
  list_remove(&focdesk->clients, c);
  stack_remove(&focdesk->focus_stack, c);
  hide_client(c);
  // focus the new best client
  if (focdesk->focus_stack != NULL)
    focus_client((client_t *)focdesk->focus_stack->value);

  // push it to the new workspace
  list_append(&desk->clients, c);
  stack_push(&desk->focus_stack, c);
  desk->focused = c;

#if FOLLOW_SEND
  focus_desktop(desk);
#endif
}

void focus_desktop(desktop_t *desk) {
  list_t *iter = focdesk->clients;
  while (iter != NULL) {
    hide_client(iter->value);
    iter = iter->next;
  }

  focdesk = desk;
  focdesk->layout.reposition(focdesk);
  focus_client(focdesk->focused);
}

void border_color(client_t *c, bool focus) {
  if (BORDER_WIDTH <= 0 || c->window == scr->root || c->window == 0)
    return;

  uint32_t vals[1] = {focus ? BORDER_COLOR_FOCUSED : BORDER_COLOR_UNFOCUSED};
  xcb_change_window_attributes(dpy, c->window, XCB_CW_BORDER_PIXEL, vals);
  xcb_flush(dpy);
}

void border_width(client_t *c, int width) {
  if (width <= 0 || c->window == scr->root || c->window == 0)
    return;

  uint32_t vals[2] = {width};
  xcb_configure_window(dpy, c->window, XCB_CONFIG_WINDOW_BORDER_WIDTH, vals);
  xcb_flush(dpy);
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

  // setup the the default desktops
  for (int i = 0; i < DEFAULT_DESKTOPS; i++)
    list_append(&desktops, new_desktop(DEFAULT_LAYOUT));
  focdesk = desktops->value; // focus the first desktop
}

void clean() {
  list_t *iter = desktops;
  while (iter != NULL) {
    desktop_t *desk = (desktop_t *)iter->value;
    list_free(desk->clients, NULL);
    iter = iter->next;
  }

  list_free(desktops, (void (*)(void *))free_desktop);
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
      /* msg("unhandled event: %s", xcb_event_str(type)); */
#endif // DEBUG
        free(ev);
    }

    if (xcb_has_error(dpy))
      running = false;
  }

  clean();
}
