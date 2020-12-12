#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>
#include <stdbool.h>
#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>

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
void _print(const char *t, const char *fmt, ...);
#define die(...) _print("FAIL", __VA_ARGS__), exit(1);
#define fail(...) _print("FAIL", __VA_ARGS__)
#define warn(...) _print("WARN", __VA_ARGS__)
#define msg(...) _print("OK", __VA_ARGS__)
#endif // DEBUG

#define SIZEOF(k) (int)(sizeof(k) / sizeof(*k))

bool xcb_has_error(xcb_connection_t *dpy);
xcb_keycode_t *xcb_get_keycode(xcb_connection_t *dpy, xcb_keysym_t keysym);
xcb_keysym_t xcb_get_keysym(xcb_connection_t *dpy, xcb_keycode_t keycode);

#endif // UTIL_H