#include "util.h"

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
