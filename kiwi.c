#include "kiwi.h"
#include "config.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <xcb/randr.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

// {{{ global declarations

// {{{ events
static void (*events[XCB_NO_OPERATION])(xcb_generic_event_t *e);

static void handle_map_request(xcb_generic_event_t *ev);
static void handle_destroy_notify(xcb_generic_event_t *ev);
static void handle_button_press(xcb_generic_event_t *ev);
static void handle_motion_notify(xcb_generic_event_t *ev);
static void handle_configure_notify(xcb_generic_event_t *ev);
static void handle_button_release(xcb_generic_event_t *ev);
#if FOCUS_TYPE
static void handle_enter_notify(xcb_generic_event_t *ev);
#endif // FOCUS_TYPE
static void handle_key_press(xcb_generic_event_t *ev);
// }}}

#define ROOT_EVENT_MASK                                                        \
  (XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | \
   XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_BUTTON_PRESS)
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define focdesk focmon->focused

list_t *monitors;
monitor_t *focmon;
xcb_connection_t *dpy = NULL;
xcb_screen_t *scr = NULL;
int desktop_count = 0;
// }}}

/// {{{ debugging utils & wm status functionality
// info print
#ifdef DEBUG
void _print(const char *t, const char *fn, const char *f, const int l,
            const char *fmt, ...);
#define die(...)                                                               \
  _print("FAIL", __func__, __FILE__, __LINE__, __VA_ARGS__), exit(1);
#define fail(...) _print("FAIL", __func__, __FILE__, __LINE__, __VA_ARGS__)
#define warn(...) _print("WARN", __func__, __FILE__, __LINE__, __VA_ARGS__)
#define msg(...) _print("OK", __func__, __FILE__, __LINE__, __VA_ARGS__)
#else
void _print(const char *t, const char *fn, const char *fmt, ...);
#define die(...) _print("FAIL", __func__, __VA_ARGS__), exit(1);
#define fail(...) _print("FAIL", __func__, __VA_ARGS__)
#define warn(...) _print("WARN", __func__, __VA_ARGS__)
#define msg(...) _print("OK", __func__, __VA_ARGS__)
#endif // DEBUG

#define SIZEOF(k) (int)(sizeof(k) / sizeof(*k))
#define UNUSED(x) (void)(x)

#ifdef DEBUG
void _print(const char *t, const char *fn, const char *f, const int l,
            const char *fmt, ...) {
#else
void _print(const char *t, const char *fn, const char *fmt, ...) {
#endif // DEBUG
  va_list args;

  va_start(args, fmt);

#ifdef DEBUG
  printf("[%s] (%s in %s:%d) ", t, fn, f, l);
#else
  printf("[%s] (%s) ", fn, t);
#endif // DEBUG
  vprintf(fmt, args);
  printf("\n");

  va_end(args);
#ifdef DEBUG
  fflush(stdout);
#endif // DEBUG
}

// prints a debug message to the console and updates the WM_NAME property of the
// root window to provide info about the window manager to other tools
//
// Example:
// [("dp1",[(i+1,0|1,n),...]),("dp2",[(i+1,0|1,n),...]),...]
//
// Format:
// [...list of monitors...]
// - each monitor:
//   (name, ...list of desktops...)
//   - each desktop:
//   (desktop index(+1), focused, number of clients)
void wm_info() {
#define MAX_LEN 4096 // should be plenty of space
#define APPEND(...) len += sprintf(str + len, __VA_ARGS__)
  char str[MAX_LEN];
  int len = sprintf(str, "[");

#ifdef DEBUG
  char debug_str[9];
  printf("--------------------------------------------------------\n");
#endif // DEBUG
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    if (miter != monitors) // not first one
      APPEND(",");

    APPEND("(\"%s\",[", mon->name);
#ifdef DEBUG
    printf("%p\tmonitor (%d) -- %s (%d+%d+%dx%d)\n", (void *)mon, mon->monitor,
           mon->name, mon->x, mon->y, mon->w, mon->h);
#endif // DEBUG
    for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
      desktop_t *desk = diter->value;
      if (diter != mon->desktops) // not first one
        APPEND(",");

      APPEND("(%d,%d,%d)", desk->i + 1, mon->focused == desk,
             list_size(desk->clients));
#ifdef DEBUG
      if (mon->focused == desk)
        sprintf(debug_str, "focused");
      else
        sprintf(debug_str, "inactive");
      printf("%p\t\tdesktop (%d) -- %s\n", (void *)desk, desk->i, debug_str);

      for (list_t *citer = desk->clients; citer != NULL; citer = citer->next) {
        client_t *c = citer->value;

        if (c == desk->focused)
          sprintf(debug_str, "focused");
        else if (c->visibility == HIDDEN)
          sprintf(debug_str, "hidden");
        else
          sprintf(debug_str, "shown");

        printf("%p\t\t\tclient (%d) -- %s\n", (void *)c, c->window, debug_str);
      }
#endif // DEBUG
    }
    APPEND("])");
  }
#ifdef DEBUG
  printf("--------------------------------------------------------\n");
#endif // DEBUG
  len += sprintf(str + len, "]");
  xcb_change_property(dpy, XCB_PROP_MODE_REPLACE, scr->root, XCB_ATOM_WM_NAME,
                      XCB_ATOM_STRING, 8, len, str);
  xcb_flush(dpy);
}
#undef MAX_LEN
#undef APPEND

// }}}

// {{{ xcb utils
// taken from xwm
xcb_keysym_t xcb_get_keysym(xcb_connection_t *dpy, xcb_keycode_t keycode) {
  xcb_key_symbols_t *keysyms = xcb_key_symbols_alloc(dpy);
  xcb_keysym_t keysym;

  keysym = (!(keysyms) ? 0 : xcb_key_symbols_get_keysym(keysyms, keycode, 0));
  xcb_key_symbols_free(keysyms);

  return keysym;
}

// taken from xwm
xcb_keycode_t *xcb_get_keycode(xcb_connection_t *dpy, xcb_keysym_t keysym) {
  xcb_key_symbols_t *keysyms = xcb_key_symbols_alloc(dpy);
  xcb_keycode_t *keycode;

  keycode = (!(keysyms) ? NULL : xcb_key_symbols_get_keycode(keysyms, keysym));
  xcb_key_symbols_free(keysyms);

  return keycode;
}

// wrapper around xcb_get_geomtry for safe error handling
// NOTE: the return value MUST be freed
xcb_get_geometry_reply_t *xcb_geometry(xcb_connection_t *dpy,
                                       xcb_drawable_t drw) {
  xcb_get_geometry_cookie_t cookie = xcb_get_geometry(dpy, drw);
  xcb_generic_error_t *err = NULL;
  xcb_get_geometry_reply_t *reply = xcb_get_geometry_reply(dpy, cookie, &err);
  if (err == NULL)
    return reply;

  fail("could not get geometry for drawable %d: %d", drw, err->error_code);
  return NULL;
}

// borrowed and adjusted from bspwm.
// thank you baskerville
bool xcb_has_error(xcb_connection_t *dpy) {
  int xerr;
  if ((xerr = xcb_connection_has_error(dpy)) == 0) {
    return false;
  }

  char msg[256];
  switch (xerr) {
  case XCB_CONN_ERROR:
    strcpy(msg, "socket, pipe or stream error");
    break;
  case XCB_CONN_CLOSED_EXT_NOTSUPPORTED:
    strcpy(msg, "unsupported extension");
    break;
  case XCB_CONN_CLOSED_MEM_INSUFFICIENT:
    strcpy(msg, "not enough memory");
    break;
  case XCB_CONN_CLOSED_REQ_LEN_EXCEED:
    strcpy(msg, "request length exceeded");
    break;
  case XCB_CONN_CLOSED_PARSE_ERR:
    strcpy(msg, "can't parse display string");
    break;
  case XCB_CONN_CLOSED_INVALID_SCREEN:
    strcpy(msg, "invalid screen");
    break;
  case XCB_CONN_CLOSED_FDPASSING_FAILED:
    strcpy(msg, "failed to pass FD");
    break;
  default:
    strcpy(msg, "unknown error");
    break;
  }

  fail("The server closed the connection: %s", msg);
  return true;
}

#ifdef DEBUG
// borrowed from FrankenWM
char *xcb_event_str(int type) {
  switch (type) {
  case XCB_KEY_PRESS:
    return "XCB_KEY_PRESS";
  case XCB_KEY_RELEASE:
    return "XCB_KEY_RELEASE";
  case XCB_BUTTON_PRESS:
    return "XCB_BUTTON_PRESS";
  case XCB_BUTTON_RELEASE:
    return "XCB_BUTTON_RELEASE";
  case XCB_MOTION_NOTIFY:
    return "XCB_MOTION_NOTIFY";
  case XCB_ENTER_NOTIFY:
    return "XCB_ENTER_NOTIFY";
  case XCB_LEAVE_NOTIFY:
    return "XCB_LEAVE_NOTIFY";
  case XCB_FOCUS_IN:
    return "XCB_FOCUS_IN";
  case XCB_FOCUS_OUT:
    return "XCB_FOCUS_OUT";
  case XCB_KEYMAP_NOTIFY:
    return "XCB_KEYMAP_NOTIFY";
  case XCB_EXPOSE:
    return "XCB_EXPOSE";
  case XCB_GRAPHICS_EXPOSURE:
    return "XCB_GRAPHICS_EXPOSURE";
  case XCB_NO_EXPOSURE:
    return "XCB_NO_EXPOSURE";
  case XCB_VISIBILITY_NOTIFY:
    return "XCB_VISIBILITY_NOTIFY";
  case XCB_CREATE_NOTIFY:
    return "XCB_CREATE_NOTIFY";
  case XCB_DESTROY_NOTIFY:
    return "XCB_DESTROY_NOTIFY";
  case XCB_UNMAP_NOTIFY:
    return "XCB_UNMAP_NOTIFY ";
  case XCB_MAP_NOTIFY:
    return "XCB_MAP_NOTIFY";
  case XCB_MAP_REQUEST:
    return "XCB_MAP_REQUEST ";
  case XCB_REPARENT_NOTIFY:
    return "XCB_REPARENT_NOTIFY";
  case XCB_CONFIGURE_NOTIFY:
    return "XCB_CONFIGURE_NOTIFY";
  case XCB_CONFIGURE_REQUEST:
    return "XCB_CONFIGURE_REQUEST";
  case XCB_GRAVITY_NOTIFY:
    return "XCB_GRAVITY_NOTIFY";
  case XCB_RESIZE_REQUEST:
    return "XCB_RESIZE_REQUEST";
  default:
    return "undefined event";
  }
}
#endif // DEBUG

/// }}}

// {{{ methods on lists
void list_append(list_t **l, void *ele) {
  list_t *n = malloc(sizeof(list_t));
  n->next = NULL;
  n->value = ele;
  if (*l == NULL)
    *l = n;
  else {
    list_t *iter = *l;
    while (iter->next != NULL)
      iter = iter->next;
    iter->next = n;
  }
}

void list_remove(list_t **l, void *ele) {
  list_t *head = *l, *iter = *l, *prev = NULL;
  while (iter != NULL) {
    if (iter->value == ele) {
      list_t *tmp = iter;
      if (prev == NULL)
        head = iter->next;
      else
        prev->next = iter->next;

      iter = iter->next;
      free(tmp);
    } else {
      prev = iter;
      iter = iter->next;
    }
  }

  *l = head;
}

int list_size(list_t *iter) {
  int count = 0;
  while (iter != NULL) {
    count++;
    iter = iter->next;
  }

  return count;
}

void list_free(list_t *iter, void (*custom_free)(void *)) {
  while (iter != NULL) {
    list_t *tmp = iter;
    iter = iter->next;

    // call custom free function if required
    if (custom_free != NULL)
      custom_free(tmp->value);
    free(tmp);
  }
}
// }}}

// {{{ methods on stacks (lifo - last in first out)
// TODO: OPTIMIZE:
// don't push multiple occourcences of the same *ele
// check for existing ones and move these. lowers the memory
// and allocation buren. priority low
void stack_push(lifo_t **s, void *ele) {
  lifo_t *n = malloc(sizeof(lifo_t));
  n->prev = *s;
  n->value = ele;
  *s = n;
}

void *stack_pop(lifo_t **s) {
  lifo_t *ele = *s;
  *s = ele->prev;
  return ele->value;
}

void stack_remove(lifo_t **s, void *ele) {
  lifo_t *head = *s, *iter = *s, *prev = NULL;
  while (iter != NULL) {
    if (iter->value == ele) {
      lifo_t *tmp = iter;
      if (prev == NULL)
        head = iter->prev;
      else
        prev->prev = iter->prev;

      iter = iter->prev;
      free(tmp);
    } else {
      prev = iter;
      iter = iter->prev;
    }
  }

  *s = head;
}

void stack_free(lifo_t *iter) {
  while (iter != NULL) {
    lifo_t *tmp = iter;
    iter = iter->prev;
    free(tmp);
  }
}
// }}}

// {{{ methods on clients
// initializes a client struct
client_t *new_client(xcb_window_t w) {
#ifdef DEBUG
  if (get_client(w) != NULL)
    fail("attempted to initialize new client with an existing window %d", w);
#endif

  client_t *c = malloc(sizeof(client_t));
  c->window = w;
  c->split_ratio = SPLIT_RATIO;
  c->visibility = HIDDEN;
  c->motion = MOTION_NONE;

  xcb_get_geometry_reply_t *geom = xcb_geometry(dpy, w);
  c->x = c->floating_x = c->tiling_x =
      ((focmon->w - geom->width + BORDER_WIDTH_LEFT) / 2);
  c->y = c->floating_y = c->tiling_y =
      ((focmon->h - geom->height + BORDER_WIDTH_TOP) / 2);
  c->w = c->floating_w = c->tiling_w = geom->width;
  c->h = c->floating_h = c->tiling_h = geom->height;

  c->decour_x = c->x - BORDER_WIDTH_LEFT;
  c->decour_y = c->y - BORDER_WIDTH_TOP;
  c->decour_w = c->w + BORDER_WIDTH_LEFT + BORDER_WIDTH_RIGHT;
  c->decour_h = c->h + BORDER_WIDTH_TOP + BORDER_WIDTH_BOTTOM;

  c->decour_color = c->prev_decour_color = BORDER_COLOR_UNFOCUSED;
  new_decour(c);

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

void move_client(client_t *c, int16_t new_x, int16_t new_y) {
  if (c == NULL)
    return;

  monitor_t *mon;
  if ((mon = get_monitor_for_client(c)) == NULL)
    fail("could not get monitor for client");

  // keep the new_x and new_y between minimum and maximum values to prevent the
  // window from going off-screen
  new_x =
      MIN(mon->w - c->w - BORDER_WIDTH_RIGHT, MAX(new_x, BORDER_WIDTH_LEFT));
  new_y =
      MIN(mon->h - c->h - BORDER_WIDTH_BOTTOM, MAX(new_y, BORDER_WIDTH_TOP));
  int16_t diff_x = new_x - c->x, diff_y = new_y - c->y;

  // move the window drawable
  c->x = new_x;
  c->y = new_y;
  uint32_t values[2] = {mon->x + new_x, mon->y + new_y};
  xcb_configure_window(dpy, c->window,
                       XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, values);

  // move the decoration along with the window
  c->decour_x += diff_x;
  c->decour_y += diff_y;
  values[0] = mon->x + c->decour_x;
  values[1] = mon->y + c->decour_y;
  xcb_configure_window(dpy, c->decour,
                       XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, values);
}

void resize_client(client_t *c, uint16_t new_w, uint16_t new_h) {
  if (c == NULL)
    return;

  c->w = new_w;
  c->h = new_h;
  uint32_t values[2] = {new_w, new_h};
  xcb_configure_window(dpy, c->window,
                       XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                       values);
}

void move_resize_client(client_t *c, int16_t new_x, int16_t new_y,
                        uint16_t new_w, uint16_t new_h) {
  if (c == NULL)
    return;

  monitor_t *mon;
  if ((mon = get_monitor_for_client(c)) == NULL)
    fail("could not get monitor for client");

  c->x = new_x;
  c->y = new_y;
  c->w = new_w;
  c->h = new_h;
  uint32_t values[4] = {mon->x + new_x, mon->y + new_y, new_w, new_h};
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
    move_resize_client(c, c->x, 0, c->x, mon->h - bwy);
  else if (c->floating_h + c->floating_y + bwy > mon->h)
    move_client(c, c->x, mon->h - c->floating_h - bwy);
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
    c->floating_x = c->x;
    c->floating_y = c->y;
    c->floating_w = c->w;
    c->floating_h = c->h;
  } else {
    c->x = c->x;
    c->y = c->y;
    c->w = c->w;
    c->h = c->h;
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
  if (c == NULL)
    return;

#ifdef DEBUG
  msg("%p\tclient (%d) -- hidden", c, c->window);
#endif

  c->visibility = HIDDEN;
  toggle_window(c->window, c->visibility);
}

void show_client(client_t *c) {
  if (c == NULL)
    return;

#ifdef DEBUG
  msg("%p\tclient (%d) -- shown", c, c->window);
#endif

  c->visibility = SHOWN;
  toggle_window(c->window, c->visibility);
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

void free_client(client_t *c) {
  // clear up decoration stuff
  xcb_unmap_window(dpy, c->decour);
  xcb_free_pixmap(dpy, c->decour_pixmap);
  xcb_free_gc(dpy, c->decour_gc);
}
// }}}

// {{{ methods on dekstops
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
// }}}

// {{{ methods on monitors
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
// }}}

// {{{ keybind actions
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
// }}}

// {{{ methods on multimonitors
// most of the code for multimonitor handling is borrowed from the awesome
// windowchef project. many thanks to its authors

static void dummy_monitor();
static void get_outputs();

int randr_base = -1;

static void add_monitor(xcb_randr_output_t out, const char *name, int16_t x,
                        int16_t y, uint16_t w, int16_t h) {
  monitor_t *monitor = new_monitor(out, name, x, y, w, h);
  list_append(&monitors, monitor);
  setup_desktops(monitor);

  // use this monitor as default when none is set
  if (focmon == NULL)
    focmon = monitor;
}

// use a dummy monitor for when we can't identify monitors with randr
static void dummy_monitor() {
  monitor_t *mon;
  // update the existing monitor on resize
  if ((mon = get_monitor_by_id(0)) != NULL) {
    mon->w = scr->width_in_pixels;
    mon->h = scr->height_in_pixels;
  } else
    add_monitor(0, "dummy", 0, 0, scr->width_in_pixels, scr->height_in_pixels);
}

void get_randr() {
  xcb_randr_get_screen_resources_current_cookie_t c =
      xcb_randr_get_screen_resources_current(dpy, scr->root);
  xcb_randr_get_screen_resources_current_reply_t *r =
      xcb_randr_get_screen_resources_current_reply(dpy, c, NULL);

  if (r == NULL)
    fail("randr: could not fetch screen resources");

  xcb_timestamp_t timestamp = r->config_timestamp;
  int len = xcb_randr_get_screen_resources_current_outputs_length(r);
  xcb_randr_output_t *outputs =
      xcb_randr_get_screen_resources_current_outputs(r);

  if (len > 0)
    get_outputs(outputs, len, timestamp);
  else
    dummy_monitor();

  free(r);
  wm_info();
}

static void get_outputs(xcb_randr_output_t *outputs, int len,
                        xcb_timestamp_t timestamp) {
  xcb_randr_get_output_info_cookie_t out_cookie[len];

  for (int i = 0; i < len; i++)
    out_cookie[i] = xcb_randr_get_output_info(dpy, outputs[i], timestamp);

  for (int i = 0; i < len; i++) {
    xcb_randr_get_output_info_reply_t *output =
        xcb_randr_get_output_info_reply(dpy, out_cookie[i], NULL);
    if (output == NULL)
      continue;

    int name_len = xcb_randr_get_output_info_name_length(output);
    if (16 < name_len)
      name_len = 16;

    char *name = malloc(name_len + 1);
    // make sure the name is at most name_len + 1 length
    // or we may run into problems.
    snprintf(name, name_len + 1, "%.*s", name_len,
             xcb_randr_get_output_info_name(output));

    if (output->crtc != XCB_NONE) {
      xcb_randr_get_crtc_info_cookie_t info_c =
          xcb_randr_get_crtc_info(dpy, output->crtc, timestamp);
      xcb_randr_get_crtc_info_reply_t *crtc =
          xcb_randr_get_crtc_info_reply(dpy, info_c, NULL);

      if (crtc == NULL)
        return;

      monitor_t *mon;
      if ((mon = get_monitor_clones(outputs[i], crtc->x, crtc->y)) != NULL) {
        // when we have a clone always keep the one with the biggest resolution
        if (mon->w < crtc->width || mon->x < crtc->height)
          goto update;
      }

      mon = get_monitor_by_id(outputs[i]);
      if (mon == NULL) {
        add_monitor(outputs[i], name, crtc->x, crtc->y, crtc->width,
                    crtc->height);
      } else {
        // update position if already available
        mon->x = crtc->x;
        mon->y = crtc->y;
      update:
        mon->w = crtc->width;
        mon->h = crtc->height;

        // reposition windows on the focused desktop
        if (mon->focused != NULL)
          mon->focused->layout.reposition(mon->focused);
      }

      free(crtc);
    } else {
      // Check if the monitor was used before
      // becoming disabled.
      monitor_t *mon = get_monitor_by_id(outputs[i]);
      if (mon == NULL) {
        warn("randr: removed unregistered monitor %d", outputs[i]);
        continue;
      }
      // remove the monitor from the currently active ones
      list_remove(&monitors, mon);

      monitor_t *replacement = NULL;
      // wheter we should kill all windows since we don't have a replacement
      // monitor
      bool kill = monitors == NULL || (replacement = monitors->value) == NULL;

      // move all clients to the new replacement desktop
      for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
        desktop_t *desk = diter->value;
        for (list_t *citer = desk->clients; citer != NULL;
             citer = citer->next) {
          client_t *c = citer->value;
          if (kill)
            xcb_kill_client(dpy, c->window);
          else
            list_append(&replacement->focused->clients, c);
        }
      }

      list_free(mon->desktops, (void (*)(void *))free_desktop);
      free(mon);
      if (focmon == mon)
        focmon = mon = NULL;
    }

    free(output);
    free(name);
  }
}

void setup_randr() {
  const xcb_query_extension_reply_t *r =
      xcb_get_extension_data(dpy, &xcb_randr_id);

  if (!r->present) {
    dummy_monitor();
    return;
  }

  randr_base = r->first_event;
  get_randr();
  xcb_randr_select_input(dpy, scr->root,
                         XCB_RANDR_NOTIFY_MASK_SCREEN_CHANGE |
                             XCB_RANDR_NOTIFY_MASK_OUTPUT_CHANGE |
                             XCB_RANDR_NOTIFY_MASK_CRTC_CHANGE |
                             XCB_RANDR_NOTIFY_MASK_OUTPUT_PROPERTY);
}
// }}}

// {{{ events
static void (*events[XCB_NO_OPERATION])(xcb_generic_event_t *e) = {
  /* [XCB_CREATE_NOTIFY] = handle_create_notify, */
  [XCB_MAP_REQUEST] = handle_map_request,
  [XCB_DESTROY_NOTIFY] = handle_destroy_notify,

  [XCB_BUTTON_PRESS] = handle_button_press,
  [XCB_MOTION_NOTIFY] = handle_motion_notify,
  [XCB_CONFIGURE_NOTIFY] = handle_configure_notify,
  [XCB_BUTTON_RELEASE] = handle_button_release,

#if FOCUS_TYPE
  [XCB_ENTER_NOTIFY] = handle_enter_notify,
#endif // FOCUS_TYPE

  [XCB_KEY_PRESS] = handle_key_press,
};

static void handle_map_request(xcb_generic_event_t *ev) {
  xcb_map_request_event_t *e = (xcb_map_request_event_t *)ev;
  client_t *c = new_client(e->window);
  list_append(&focdesk->clients, c);

#if !FOCUS_TYPE
  // start grabbing for clicks on the window
  xcb_grab_button(dpy, false, c->window, XCB_EVENT_MASK_BUTTON_PRESS,
                  XCB_GRAB_MODE_SYNC, XCB_GRAB_MODE_ASYNC, XCB_NONE, XCB_NONE,
                  XCB_BUTTON_INDEX_1, XCB_NONE);
#endif
  uint32_t values[1] = {(FOCUS_TYPE ? XCB_EVENT_MASK_ENTER_WINDOW : 0) |
                        XCB_EVENT_MASK_FOCUS_CHANGE};
  xcb_change_window_attributes_checked(dpy, c->window, XCB_CW_EVENT_MASK,
                                       values);

  show_client(c);
  focus_client(c);
  focdesk->layout.reposition(focdesk);
}

static void handle_destroy_notify(xcb_generic_event_t *ev) {
  xcb_destroy_notify_event_t *e = (xcb_destroy_notify_event_t *)ev;
  client_t *c = get_client(e->window);
  if (c == NULL) // a window not handled by the window manager
    return;

  // discard any window information
  xcb_ungrab_button(dpy, XCB_BUTTON_INDEX_1, c->window, XCB_NONE);
  xcb_kill_client(dpy, c->window);

  // the focdesk may be null as the monitor the window was on was unplugged
  if (focdesk != NULL) {
    list_remove(&focdesk->clients, c);
    stack_remove(&focdesk->focus_stack, c);
    if (focdesk->focused == c)
      focdesk->focused = NULL;

    // focus the new best client
    if (focdesk->focus_stack != NULL)
      focus_client((client_t *)focdesk->focus_stack->value);
    focdesk->layout.reposition(focdesk);
  }
}

static int16_t start_x, start_y;
static void handle_button_press(xcb_generic_event_t *ev) {
  xcb_button_press_event_t *e = (xcb_button_press_event_t *)ev;
  client_t *c = get_client(e->state < MODKEY ? e->event : e->child);
  monitor_t *mon = get_monitor_by_coords(e->root_x, e->root_y);
  if (mon != NULL)
    focus_monitor(mon);

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

  start_x = e->root_x;
  start_y = e->root_y;
  if (e->detail == 1)
    c->motion = MOTION_DRAGGING;
  else
    c->motion = MOTION_RESIZING;

  xcb_grab_pointer(dpy, false, scr->root,
                   XCB_EVENT_MASK_BUTTON_RELEASE |
                       XCB_EVENT_MASK_BUTTON_MOTION |
                       XCB_EVENT_MASK_POINTER_MOTION_HINT,
                   XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC, scr->root,
                   XCB_NONE, XCB_CURRENT_TIME);
}

static void handle_motion_notify(xcb_generic_event_t *ev) {
  UNUSED(ev);
  xcb_query_pointer_cookie_t coord = xcb_query_pointer(dpy, scr->root);
  xcb_query_pointer_reply_t *pointer = xcb_query_pointer_reply(dpy, coord, 0);
  rel_pointer_t p = {
      .x = pointer->root_x - start_x,
      .y = pointer->root_y - start_y,
  };
  free(pointer);
  focdesk->layout.motion(p, focdesk->focused, focmon);
}

static void handle_configure_notify(xcb_generic_event_t *ev) {
  xcb_configure_notify_event_t *e = (xcb_configure_notify_event_t *)ev;
  if (e->window == 0 || e->window == scr->root) {
    // if the dimentions have changed update the root window sizes
    if (e->width != scr->width_in_pixels ||
        e->height != scr->height_in_pixels) {
      scr->width_in_pixels = e->width;
      scr->height_in_pixels = e->height;

      if (randr_base != -1) {
        get_randr();
        for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
          desktop_t *desk = ((monitor_t *)miter->value)->focused;
          if (desk != NULL)
            desk->layout.reposition(desk);
        }
      }
    }
  } else {
    client_t *c = get_client(e->window);
    if (c == NULL || c->motion != MOTION_NONE || c->visibility == HIDDEN)
      return;

    c->x = e->x;
    c->y = e->y;
    c->w = e->width;
    c->h = e->height;
  }
}

static void handle_button_release(xcb_generic_event_t *ev) {
  UNUSED(ev);
  if (focdesk->focused != NULL) {
    focdesk->focused->motion = MOTION_NONE;
    save_client(focdesk->focused, focdesk->layout.type);
  }

  xcb_ungrab_pointer(dpy, XCB_CURRENT_TIME);
}

#if FOCUS_TYPE
static void handle_enter_notify(xcb_generic_event_t *ev) {
  xcb_enter_notify_event_t *e = (xcb_enter_notify_event_t *)ev;
  client_t *c = get_client(e->event);
  focus_client(c);
}
#endif // FOCUS_TYPE

static void handle_key_press(xcb_generic_event_t *ev) {
  xcb_key_press_event_t *e = (xcb_key_press_event_t *)ev;
  xcb_keysym_t keysym = xcb_get_keysym(dpy, e->detail);
  int key_table_size = sizeof(keys) / sizeof(*keys);

  for (int i = 0; i < key_table_size; ++i) {
    if ((keys[i].keysym == keysym) && (keys[i].mod == e->state)) {
      keys[i].func(keys[i].arg);
    }
  }
}
// }}}

// {{{ layouts
static void floating_reposition(desktop_t *desk);
static void floating_motion(rel_pointer_t p, client_t *c, monitor_t *mon);
static void floating_move(enum direction d, client_t *c, desktop_t *desk);
static void tiling_reposition(desktop_t *desk);
static void tiling_motion(rel_pointer_t p, client_t *c, monitor_t *mon);
static void tiling_move(enum direction d, client_t *c, desktop_t *desk);

const layout_t floating_layout = {
    .type = LAYOUT_FLOATING,
    .reposition = floating_reposition,
    .motion = floating_motion,
    .move = floating_move,
};
const layout_t tiling_layout = {
    .type = LAYOUT_TILING,
    .reposition = tiling_reposition,
    .motion = tiling_motion,
    .move = tiling_move,
};

// just shows hidden windows as they are moved manually by the user
static void floating_reposition(desktop_t *desk) {
  monitor_t *mon = get_monitor_for_desktop(desk);
  for (list_t *iter = desk->clients; iter != NULL; iter = iter->next) {
    client_t *c = iter->value;
    // restore its previous position
    move_resize_client(c, c->floating_x, c->floating_y, c->floating_w,
                       c->floating_h);
    // fit the client to its new monitor, if needed
    fit_client(c, mon);

    if (c->visibility == HIDDEN)
      show_client(c);
  }
}

static void floating_motion(rel_pointer_t p, client_t *c, monitor_t *mon) {
  UNUSED(mon);
  uint16_t bwx = BORDER_WIDTH_LEFT + BORDER_WIDTH_RIGHT;
  uint16_t bwy = BORDER_WIDTH_TOP + BORDER_WIDTH_BOTTOM;
  if (c->motion == MOTION_DRAGGING) {
    move_client(c, c->floating_x + p.x, c->floating_y + p.y);
  } else if (c->motion == MOTION_RESIZING) {
    int16_t w =
        MIN(mon->w - c->floating_x - bwx, MAX(c->floating_w + p.x, MIN_WIDTH));
    int16_t h =
        MIN(mon->h - c->floating_y - bwy, MAX(c->floating_h + p.y, MIN_HEIGHT));
    resize_client(c, w, h);
  }
}

static void floating_move(enum direction d, client_t *c, desktop_t *desk) {
  monitor_t *mon = get_monitor_for_desktop(desk);
  rel_pointer_t p = {0, 0};
  switch (d) {
  case DIRECTION_LEFT:
    p.x = -MOVE_STEP;
    break;
  case DIRECTION_RIGHT:
    p.x = MOVE_STEP;
    break;
  case DIRECTION_BOTTOM:
    p.y = MOVE_STEP;
    break;
  case DIRECTION_TOP:
    p.y = -MOVE_STEP;
    break;
  }
  c->motion = MOTION_DRAGGING;
  floating_motion(p, c, mon);
  save_client(c, LAYOUT_FLOATING);
  c->motion = MOTION_NONE;
}

// checks whether there is any following client to be drawn and returns true if
// there are none (which means the current one should fill all the remaining
// space)
static bool should_fill(list_t *iter) {
  return iter->next == NULL || iter->next->value == NULL;
}

// repositions the windows in the tiling style.
// the first windows is called the "main" window and is,
// positioned to the left,while all others "secondary"
// windows to be stacked one upon the other to the right.
static void tiling_reposition(desktop_t *desk) {
  monitor_t *mon = get_monitor_for_desktop(desk);
  if (mon == NULL)
    fail("could not get monitor for desktop");

  int16_t x = SCREEN_GAPS, y = SCREEN_GAPS;
  uint16_t w = mon->w - SCREEN_GAPS, h = mon->h - SCREEN_GAPS,
           bw = BORDER_TILING * 2;
  client_t *first = desk->clients->value;

  for (list_t *iter = desk->clients; iter != NULL; iter = iter->next) {
    bool fill = should_fill(iter->next);
    int width, height;
    client_t *c = iter->value;
    if (c == NULL)
      continue;

    if (c == first) {
      // drawing the main window
      width = (fill ? w : w * c->split_ratio) - bw;
      height = h - bw;
    } else {
      // drawing any seconday windows
      width = w - bw;
      height = (fill ? h : h * c->split_ratio) - bw;
    }

    move_resize_client(c, x, y, width, height);
    save_client(c, LAYOUT_TILING);

    if (c == first) {
      w -= width + bw;
      x = width + bw;
    } else {
      h -= height + bw;
      y += height + bw;
    }
  }
}

static void tiling_motion(rel_pointer_t p, client_t *c, monitor_t *mon) {
  UNUSED(p);
  UNUSED(c);
  UNUSED(mon);
}

static void tiling_move(enum direction d, client_t *c, desktop_t *desk) {
  // if we're focusing the last element of the list updating its
  // split ratio won't have effect.
  // TODO: discuss this implementation
  switch (d) {
  case DIRECTION_LEFT:
  case DIRECTION_BOTTOM:
    c->split_ratio -= 0.05;
    break;
  case DIRECTION_RIGHT:
  case DIRECTION_TOP:
    c->split_ratio += 0.05;
    break;
  }

  tiling_reposition(desk);
}
// }}}

// {{{ methods on decorations
void new_decour(client_t *c) {
  uint32_t values[2], mask;

  // make the pixmap for the window
  c->decour_pixmap = xcb_generate_id(dpy);
  xcb_create_pixmap(dpy, scr->root_depth, c->decour_pixmap, scr->root,
                    c->decour_w, c->decour_h);

  // create the window
  c->decour = xcb_generate_id(dpy);
  mask = XCB_CW_BACK_PIXMAP /* | XCB_CW_EVENT_MASK*/;
  values[0] = c->decour_pixmap;
  // TODO: we could listen for grabs so we can move windows by titlebars
  xcb_create_window(dpy, scr->root_depth, c->decour, scr->root, c->decour_x,
                    c->decour_y, c->decour_w, c->decour_h, 0,
                    XCB_WINDOW_CLASS_INPUT_OUTPUT, scr->root_visual, mask,
                    values);

  // create a context for filling with the given color
  c->decour_gc = xcb_generate_id(dpy);
  mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND;
  values[0] = values[1] = c->decour_color;
  xcb_create_gc(dpy, c->decour_gc, scr->root, mask, values);

  xcb_poly_fill_rectangle(
      dpy, c->decour_pixmap, c->decour_gc, 1,
      (xcb_rectangle_t[]){
          {.x = 0, .y = 0, .width = c->decour_w, .height = c->decour_h}});
  xcb_map_window(dpy, c->decour);
}

// updates the client's decorations
void decorate_client(client_t *c) {
  if (c == NULL || c->prev_decour_color == c->decour_color)
    return;

  msg("bordering client");
  c->prev_decour_color = c->decour_color;
}
// }}}

// {{{ lifecycle methods
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
      list_free(desk->clients, (void (*)(void *))free_client);
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
// }}}

// vim: set foldmethod=marker foldmarker={{{,}}}:
