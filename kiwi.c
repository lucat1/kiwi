#include "kiwi.h"
#include "config.h"
#include "events.h"
#include "layouts.h"
#include "randr.h"
#include "util.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <xcb/randr.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

#define ROOT_EVENT_MASK                                                        \
  (XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | \
   XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_BUTTON_PRESS)

list_t *monitors;
monitor_t *focmon;
xcb_connection_t *dpy = NULL;
xcb_screen_t *scr = NULL;
int desktop_count = 0;

// initializes a client struct
client_t *new_client(xcb_window_t w) {
#ifdef DEBUG
  if (get_client(w) != NULL)
    fail("attempted to initialize new client with an existing window %d", w);
#endif

  client_t *c = malloc(sizeof(client_t));
  c->window = w;
  c->mapped = false;
  c->split_ratio = SPLIT_RATIO;
  c->visibility = HIDDEN;
  c->motion = MOTION_NONE;

  xcb_get_geometry_reply_t *geom = xcb_geometry(dpy, w);
  c->actual_x = c->x = c->floating_x = (focmon->w - geom->width) / 2;
  c->actual_y = c->y = c->floating_y = (focmon->h - geom->height) / 2;
  c->actual_w = c->w = c->floating_w = geom->width;
  c->actual_h = c->h = c->floating_h = geom->height;

  create_decour(c);
  c->decour_color = BORDER_COLOR_UNFOCUSED;

  free(geom);
  return c;
}

client_t *get_client(xcb_window_t w) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
      desktop_t *desk = diter->value;
      for (list_t *citer = desk->clients; citer != NULL; citer = citer->next) {
        client_t *c = (client_t *)citer->value;
        if (c->window == w)
          return c;
      }
    }
  }

  return NULL;
}

// initializes a desktop struct
desktop_t *new_desktop(layout_t l) {
  desktop_t *desk = malloc(sizeof(desktop_t));
  desk->i = desktop_count++;
  desk->layout = l;
  desk->clients = NULL;
  desk->focused = NULL;
  desk->focus_stack = NULL;

  return desk;
}

desktop_t *get_desktop(int i) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
      desktop_t *desk = diter->value;
      if (desk->i == i)
        return desk;
    }
  }

  return NULL;
}

void free_desktop(desktop_t *list) {
  stack_free(list->focus_stack);
  desktop_count--;
}

monitor_t *new_monitor(xcb_randr_output_t monitor, const char *name, int16_t x,
                       int16_t y, uint16_t w, uint16_t h) {
  monitor_t *mon = malloc(sizeof(monitor_t));
  mon->monitor = monitor;
  mon->name = name;
  mon->x = x;
  mon->y = y;
  mon->w = w;
  mon->h = h;
  mon->focused = NULL;
  mon->desktops = NULL;
  return mon;
}

// returns the monitor which contains the requested desktop
monitor_t *get_monitor_for_desktop(desktop_t *desk) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
      desktop_t *desktop = diter->value;
      if (desktop == desk)
        return mon;
    }
  }
  return NULL;
}

monitor_t *get_monitor_for_client(client_t *c) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
      desktop_t *desk = diter->value;
      for (list_t *citer = desk->clients; citer != NULL; citer = citer->next) {
        client_t *client = citer->value;
        if (client == c)
          return mon;
      }
    }
  }

  return NULL;
}

// find a monitor in the mirror list by its xcb identifier
monitor_t *get_monitor_by_id(xcb_randr_output_t m) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    if (mon->monitor == m)
      return mon;
  }

  return NULL;
}

// find a monitor by its coordinates
monitor_t *get_monitor_by_coords(int16_t x, int16_t y) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    // mon->x < x < mon->x+mon->w
    // mon->y < y < mon->y+mon->h
    if ((x >= mon->x && x <= (mon->x + mon->w)) &&
        (y >= mon->y && y <= (mon->y + mon->h)))
      return mon;
  }

  return NULL;
}

// find cloned (mirrored) outputs
monitor_t *get_monitor_clones(xcb_randr_output_t m, int16_t x, int16_t y) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    if (mon->monitor != m && mon->x == x && mon->y == y)
      return mon;
  }
  return NULL;
}

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
  if (focdesk->focused != NULL)
    focdesk->layout.move(arg.d, focdesk->focused, focdesk);
}

void focus_client(client_t *c) {
  if (c == NULL || (c->window == 0 && c->window == scr->root))
    return;

  // remove focus from the previous client
  if (focdesk->focused != NULL) {
    focdesk->focused->decour_color = UNFOCUSED;
    decorate_client(c);
  }

  // focus the new client
  focdesk->focused = c;
  c->decour_color = FOCUSED;
  decorate_client(c);

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
  wm_info();
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

  uint16_t bwx = BORDER_WIDTH_LEFT + BORDER_WIDTH_RIGHT;
  uint16_t bwy = BORDER_WIDTH_TOP + BORDER_WIDTH_BOTTOM;
  if (c->floating_w + bwx > mon->w)
    move_resize_client(c, 0, c->floating_y, mon->w - bwx, c->floating_h);
  else if (c->floating_w + c->floating_x + bwx > mon->w)
    move_client(c, mon->w - c->floating_w - bwx, c->floating_y);
#ifdef DEBUG
#ifdef VERBOSE
  else
    msg("%p\tno x-movement to do", c);
#endif // VERBOSE
#endif // DEBUG

  if (c->floating_h + bwy > mon->h)
    move_resize_client(c, c->actual_x, 0, c->actual_x, mon->h - bwy);
  else if (c->floating_h + c->floating_y + bwy > mon->h)
    move_client(c, c->actual_x, mon->h - c->floating_h - bwy);
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
void toggle_window(xcb_window_t win, enum visibility v) {
#ifdef DEBUG
  msg("\ttoggling window %d", win);
#endif // DEBUG
  uint32_t values_off[] = {ROOT_EVENT_MASK &
                           ~XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY};
  uint32_t values_on[] = {ROOT_EVENT_MASK};
  xcb_change_window_attributes(dpy, scr->root, XCB_CW_EVENT_MASK, values_off);
  if (v == SHOWN) {
    /* set_window_state(win, XCB_ICCCM_WM_STATE_NORMAL); */
    xcb_map_window(dpy, win);
  } else {
    xcb_unmap_window(dpy, win);
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
  toggle_window(c->window, c->visibility);
}

void show_client(client_t *c) {
  if (c == NULL || !c->mapped)
    return;

#ifdef DEBUG
  msg("%p\tclient (%d) -- shown", c, c->window);
#endif

  c->visibility = SHOWN;
  toggle_window(c->window, c->visibility);
}

bool is_decour(xcb_window_t w) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
      desktop_t *desk = diter->value;
      for (list_t *citer = desk->clients; citer != NULL; citer = citer->next) {
        client_t *c = citer->value;
        if (c->decour == w)
          return true;
      }
    }
  }
  return false;
}

void create_decour(client_t *c) {
  uint32_t values[2], mask;

  // make the pixmap for the window
  c->decour_pixmap = xcb_generate_id(dpy);
  xcb_create_pixmap(dpy, scr->root_depth, c->decour_pixmap, scr->root,
                    c->w + BORDER_WIDTH_LEFT + BORDER_WIDTH_RIGHT,
                    c->h + BORDER_WIDTH_TOP + BORDER_WIDTH_BOTTOM);

  // create a context for filling with the given color
  c->decour_gc = xcb_generate_id(dpy);
  mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND;
  values[0] = values[1] = c->decour_color;
  xcb_create_gc(dpy, c->decour_gc, 0, mask, values);

  // create the window
  c->decour = xcb_generate_id(dpy);
  mask = XCB_CW_BACK_PIXMAP /* | XCB_CW_EVENT_MASK*/;
  values[0] = c->decour_pixmap;
  // TODO: we could listen for grabs so we can move windows by titlebars
  uint16_t width = c->w + BORDER_WIDTH_LEFT + BORDER_WIDTH_RIGHT,
           height = c->h + BORDER_WIDTH_TOP + BORDER_WIDTH_BOTTOM;
  msg("width %d, height %d", width, height);
  xcb_create_window(dpy, scr->root_depth, c->decour, scr->root,
                    c->x - BORDER_WIDTH_LEFT, c->y - BORDER_WIDTH_TOP, width,
                    height, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, scr->root_visual,
                    mask, values);
  xcb_map_window(dpy, c->decour);

  xcb_poly_fill_rectangle(dpy, c->decour_pixmap, c->decour_gc, 1,
                          (xcb_rectangle_t[]){{0, 0, width, height}});
  /* xcb_free_pixmap(dpy, c->decour_pixmap); */
  /* xcb_free_gc(dpy, c->decour_gc); */
}

// updates the client's decorations
void decorate_client(client_t *c) {
  if (c == NULL)
    return;

  msg("bordering client");
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
  wm_info();
}

void focus_monitor(monitor_t *mon) {
  if (mon == focmon)
    return;

  for (list_t *iter = monitors; iter != NULL; iter = iter->next) {
    monitor_t *m = iter->value;
    if (m->focused == NULL || m->focused->focused == NULL)
      continue;

    client_t *c = m->focused->focused;
    if (m == mon)
      c->decour_color = UNFOCUSED;
    else
      c->decour_color = FOCUSED_ANOTHER_MONITOR;
    decorate_client(c);
  }

  focmon = mon;
  wm_info();
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
