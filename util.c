#include "util.h"
#include "kiwi.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#include <xcb/xproto.h>

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
  printf("[%s] (%s)", fn, t);
#endif // DEBUG
  vprintf(fmt, args);
  printf("\n");

  va_end(args);
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
    strcpy(msg, "socket, pipe or stream error.");
    break;
  case XCB_CONN_CLOSED_EXT_NOTSUPPORTED:
    strcpy(msg, "unsupported extension.");
    break;
  case XCB_CONN_CLOSED_MEM_INSUFFICIENT:
    strcpy(msg, "not enough memory.");
    break;
  case XCB_CONN_CLOSED_REQ_LEN_EXCEED:
    strcpy(msg, "request length exceeded.");
    break;
  case XCB_CONN_CLOSED_PARSE_ERR:
    strcpy(msg, "can't parse display string.");
    break;
  case XCB_CONN_CLOSED_INVALID_SCREEN:
    strcpy(msg, "invalid screen.");
    break;
  case XCB_CONN_CLOSED_FDPASSING_FAILED:
    strcpy(msg, "failed to pass FD.");
    break;
  default:
    strcpy(msg, "unknown error.");
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

static int mapped_clients_size(list_t *l) {
  int size = 0;
  for (; l != NULL; l = l->next) {
    if (((client_t *)l->value)->mapped)
      size++;
  }
  return size;
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
             mapped_clients_size(desk->clients));
#ifdef DEBUG
      if (mon->focused == desk)
        sprintf(debug_str, "focused");
      else
        sprintf(debug_str, "inactive");
      printf("%p\t\tdesktop (%d) -- %s\n", (void *)desk, desk->i, debug_str);
#endif // DEBUG

      for (list_t *citer = desk->clients; citer != NULL; citer = citer->next) {
        client_t *c = citer->value;

#ifdef DEBUG
        if (c == desk->focused)
          sprintf(debug_str, "focused");
        else if (c->visibility == HIDDEN)
          sprintf(debug_str, "hidden");
        else
          sprintf(debug_str, "shown");

        printf("%p\t\t\tclient (%d) -- [%d] %s\n", (void *)c, c->window,
               c->mapped, debug_str);
#endif // DEBUG
      }
    }
    APPEND("])");
  }
#if DEBUG
  printf("--------------------------------------------------------\n");
#endif // DEBUG
  len += sprintf(str + len, "]");
  xcb_change_property(dpy, XCB_PROP_MODE_REPLACE, scr->root, XCB_ATOM_WM_NAME,
                      XCB_ATOM_STRING, 8, len, str);
  xcb_flush(dpy);
}
#undef MAX_LEN
#undef APPEND

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

  fail("could not get geometry: %d", err->error_code);
  return NULL;
}
