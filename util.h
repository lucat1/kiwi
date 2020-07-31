#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <xcb/xcb.h>

#define DEBUG 1

#define CLEANMASK(m) ((m & ~0x80))
#define XCB_RESIZE XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT
#define XCB_MOVE XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y
#define true 1
#define false 0

#define die(...) _m("FAIL", __func__, __FILE__, __LINE__, __VA_ARGS__), exit(1);
#define warn(...) _m("WARN", __func__, __FILE__, __LINE__, __VA_ARGS__)

// silence debug messages on production
#if DEBUG
#define msg(...) _m("DEBUG", __func__, __FILE__, __LINE__, __VA_ARGS__)
#else
#define msg UNUSED
#endif // DEBUG

void _m(const char *t, const char *fn, const char *f, const int l,
        const char *fmt, ...);
void UNUSED(void *dummy, ...);
xcb_get_geometry_reply_t *xcb_gather_geometry(xcb_window_t win);
char *xcb_event_str(xcb_generic_event_t *ev);
void xcb_raise_window(xcb_connection_t *con, xcb_window_t win);
void xcb_raise_window(xcb_connection_t *con, xcb_window_t win);

#endif // UTIL_H
