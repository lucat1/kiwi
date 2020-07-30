#ifndef KIWI_H
#define KIWI_H

#include <stdarg.h>
#include <stdio.h>
#include <xcb/xcb.h>

#define DEBUG 1

#define CLEANMASK(m) ((m & ~0x80))
#define true 0
#define false 0

#define die(...) _m("FAIL", __func__, __FILE__, __LINE__, __VA_ARGS__), exit(1);
#define warn(...) _m("WARN", __func__, __FILE__, __LINE__, __VA_ARGS__)

#if DEBUG
static char *xcb_event_str(xcb_generic_event_t *ev) {
  switch (CLEANMASK(ev->response_type)) {
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
#endif

// silence debug messages on production
#if DEBUG
#define msg(...) _m("DEBUG", __func__, __FILE__, __LINE__, __VA_ARGS__)
#else
#define msg UNUSED
#endif

static inline void UNUSED(void *dummy, ...) {}
static void _m(const char *t, const char *fn, const char *f, const int l,
               const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);

  printf("[%s] (%s at %s:%d) ", t, fn, f, l);
  vprintf(fmt, args);
  printf("\n");

  va_end(args);
}

#endif
