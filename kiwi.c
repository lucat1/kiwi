#include "kiwi.h"
#include "config.h"
#include "data.h"
#include "events.h"
#include "layouts.h"
#include "randr.h"
#include "util.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

#define ROOT_EVENT_MASK                                                        \
  (XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | \
   XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_BUTTON_PRESS)

list_t *monitors;
monitor_t *focmon;
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

void set_layout(FN_ARG arg) {
  switch (arg.l) {
  case LAYOUT_FLOATING:
    focdesk->layout = floating_layout;
    break;

  case LAYOUT_TILING:
    focdesk->layout = tiling_layout;
    break;

  default:
    fail("invalid layout");
  }
  focdesk->layout.reposition(focdesk);
}

void move(FN_ARG arg) {
  focdesk->layout.move(arg.d, focdesk->focused, focdesk);
}

void focus_client(client_t *c) {
  if (c == NULL || (c->window == 0 && c->window == scr->root))
    return;

  // remove focus from the previous client
  if (focdesk->focused != NULL)
    border_color(focdesk->focused, UNFOCUSED);

  // focus the new client
  focdesk->focused = c;
  border_color(focdesk->focused, FOCUSED);

  // push the client to the focus list if we have an empty one or
  // the client isn't already at the top of it
  if ((focdesk->focus_stack != NULL && focdesk->focus_stack->value != c) ||
      focdesk->focus_stack == NULL)
    stack_push(&focdesk->focus_stack, c);

  // move the focused window above all others and set the input focus
  static const uint32_t v[] = {XCB_STACK_MODE_ABOVE};
  xcb_configure_window(dpy, c->window, XCB_CONFIG_WINDOW_STACK_MODE, v);
  xcb_set_input_focus(dpy, XCB_INPUT_FOCUS_POINTER_ROOT, c->window,
                      XCB_CURRENT_TIME);
  xcb_flush(dpy);

#ifdef DEBUG
  print_monitors();
#endif // DEBUG
}

void move_client(client_t *c, int16_t x, int16_t y) {
  if (c == NULL)
    return;

  monitor_t *mon;
  if ((mon = get_monitor_for_client(c)) == NULL)
    fail("could not get monitor for client");

  c->actual_x = x;
  c->actual_y = y;
  uint32_t values[2] = {mon->x + x, mon->y + y};
  xcb_configure_window(dpy, c->window,
                       XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, values);
}

void resize_client(client_t *c, uint16_t w, uint16_t h) {
  if (c == NULL)
    return;

  c->actual_w = w;
  c->actual_h = h;
  uint32_t values[2] = {w, h};
  xcb_configure_window(dpy, c->window,
                       XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                       values);
}

void move_resize_client(client_t *c, int16_t x, int16_t y, uint16_t w,
                        uint16_t h) {
  if (c == NULL)
    return;

  monitor_t *mon;
  if ((mon = get_monitor_for_client(c)) == NULL)
    fail("could not get monitor for client");

  c->actual_x = x;
  c->actual_y = y;
  c->actual_w = w;
  c->actual_h = h;
  uint32_t values[4] = {mon->x + x, mon->y + y, w, h};
  xcb_configure_window(dpy, c->window,
                       XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y |
                           XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                       values);
}

// fits a client to its new monitor (only needed for floating mode)
void fit_client(client_t *c, monitor_t *mon) {
#ifdef DEBUG
  msg("%p\tfitting client %d (%d+%d+%dx%d) to monior %s (%d+%d+%dx%d)", c,
      c->window, c->x, c->y, c->w, c->h, mon->name, mon->x, mon->y, mon->w,
      mon->h);
#endif // DEBUG

  int bw = BORDER_WIDTH * 2;
  if (c->floating_w + bw > mon->w)
    move_resize_client(c, 0, c->floating_y, mon->w - bw, c->floating_h);
  else if (c->floating_w + c->floating_x + bw > mon->w)
    move_client(c, mon->w - c->floating_w - bw, c->floating_y);
#ifdef DEBUG
#ifdef VERBOSE
  else
    msg("%p\tno x-movement to do", c);
#endif // VERBOSE
#endif // DEBUG

  if (c->floating_h + bw > mon->h)
    move_resize_client(c, c->actual_x, 0, c->actual_x, mon->h - bw);
  else if (c->floating_h + c->floating_y + bw > mon->h)
    move_client(c, c->actual_x, mon->h - c->floating_h - bw);
#ifdef DEBUG
#ifdef VERBOSE
  else
    msg("%p\tno y-movement to do", c);
#endif // VERBOSE
#endif // DEBUG

  save_client(c, LAYOUT_FLOATING);
}

// saves the actual coordinates into the mode-specific ones
void save_client(client_t *c, enum layout_type t) {
  if (t == LAYOUT_FLOATING) {
    c->floating_x = c->actual_x;
    c->floating_y = c->actual_y;
    c->floating_w = c->actual_w;
    c->floating_h = c->actual_h;
  } else {
    c->x = c->actual_x;
    c->y = c->actual_y;
    c->w = c->actual_w;
    c->h = c->actual_h;
  }
}

// borrowed from bspwm
void toggle_client(client_t *c) {
  uint32_t values_off[] = {ROOT_EVENT_MASK &
                           ~XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY};
  uint32_t values_on[] = {ROOT_EVENT_MASK};
  xcb_change_window_attributes(dpy, scr->root, XCB_CW_EVENT_MASK, values_off);
  if (c->visibility == SHOWN) {
    /* set_window_state(win, XCB_ICCCM_WM_STATE_NORMAL); */
    xcb_map_window(dpy, c->window);
  } else {
    xcb_unmap_window(dpy, c->window);
    /* set_window_state(win, XCB_ICCCM_WM_STATE_ICONIC); */
  }
  xcb_change_window_attributes(dpy, scr->root, XCB_CW_EVENT_MASK, values_on);
}

void hide_client(client_t *c) {
  if (c == NULL || !c->mapped)
    return;

#ifdef DEBUG
  msg("%p\tclient (%d) -- hidden", c, c->window);
#endif

  c->visibility = HIDDEN;
  toggle_client(c);
}

void show_client(client_t *c) {
  if (c == NULL || !c->mapped)
    return;

#ifdef DEBUG
  msg("%p\tclient (%d) -- shown", c, c->window);
#endif

  c->visibility = SHOWN;
  toggle_client(c);
}

void send_client(client_t *c, int i) {
  if (i < 0 || c == NULL)
    return;

  desktop_t *desk = get_desktop(i);
  // don't send a client to the same desktop it's already on
  if (desk == focdesk)
    return;
  if (desk == NULL)
#if CREATE_DESKTOP_IF_NOT_EXISTS
    while (desktop_count <= i) {
      desk = new_desktop(DEFAULT_LAYOUT);
      list_append(&focmon->desktops, desk);
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

  // show the window if it's already on a visible desktop in another monitor
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    if (mon->focused == desk) {
      show_client(c);
      desk->layout.reposition(desk);
    }
  }

#if FOLLOW_SEND
  focus_desktop(desk);
#endif
}

void focus_desktop(desktop_t *desk) {
  if (desk->i == focdesk->i)
    return;

  monitor_t *mon = get_monitor_for_desktop(desk);
  if (mon == NULL)
    die("could not find monitor for desktop");

#ifdef DEBUG
  msg("desktop %d --> %d", focdesk->i, desk->i);
  msg("monitor %d --> %d", focmon->monitor, mon->monitor);
#endif // DEBUG

  // only hide the current windows if we're changing to a desktop on the same
  // monitor
  if (mon == focmon)
    for (list_t *citer = focdesk->clients; citer != NULL; citer = citer->next) {
      hide_client(citer->value);
    }

  focus_monitor(mon);
  focmon->focused = desk;
  focdesk->layout.reposition(focdesk);
  for (list_t *citer = focdesk->clients; citer != NULL; citer = citer->next) {
    show_client(citer->value);
  }
  focus_client(focdesk->focused);
#ifdef DEBUG
  print_monitors();
#endif // DEBUG
}

void focus_monitor(monitor_t *mon) {
  if (mon == focmon)
    return;

  for (list_t *iter = monitors; iter != NULL; iter = iter->next) {
    monitor_t *m = iter->value;
    if (m->focused->focused == NULL)
      continue;

    if (m == mon)
      border_color(m->focused->focused, UNFOCUSED);
    else
      border_color(m->focused->focused, FOCUSED_ANOTHER_MONITOR);
  }

  focmon = mon;
}

void border_color(client_t *c, enum focus_type f) {
  if (BORDER_WIDTH <= 0 || c->window == scr->root || c->window == 0)
    return;

  uint32_t vals[1];
  switch (f) {
  case FOCUSED:
    vals[0] = BORDER_COLOR_FOCUSED;
    break;
  case FOCUSED_ANOTHER_MONITOR:
    vals[0] = BORDER_COLOR_FOCUSED_ANOTHER;
    break;
  case UNFOCUSED:
    vals[0] = BORDER_COLOR_UNFOCUSED;
    break;
  }
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

  if (list_size(monitors) < 1)
    die("randr: no monitors found");

  // focus the first monitor
  focmon = monitors->value;
}

void setup_desktops(monitor_t *mon) {
  for (int i = 0; i < DEFAULT_DESKTOPS; i++)
    list_append(&mon->desktops, new_desktop(DEFAULT_LAYOUT));
  mon->focused = mon->desktops->value;
}

void clean() {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
      desktop_t *desk = diter->value;
      list_free(desk->clients, NULL);
    }
    list_free(mon->desktops, (void (*)(void *))free_desktop);
  }
  list_free(monitors, NULL);
}

int main() {
  dpy = xcb_connect(NULL, NULL);
  if (xcb_has_error(dpy))
    return 1;

  scr = xcb_setup_roots_iterator(xcb_get_setup(dpy)).data;
  setup_randr();
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
#ifdef VERBOSE
      else
        msg("unhandled event: %s", xcb_event_str(type));
#endif // VERBOSE
#endif // DEBUG
      free(ev);
    }

    if (xcb_has_error(dpy))
      running = false;
  }

  clean();
}
