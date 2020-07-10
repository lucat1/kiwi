#ifndef KIWI_H
#define KIWI_H

#include <X11/Xlib.h>
#include <stdarg.h>
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MOUSEMASK (PointerMotionMask | ButtonPressMask | ButtonReleaseMask)

#define MAXLEN 256
#define AUTOSTART "kiwi/autostart"
#define MINIMUM_DIM 100

#define die(...)                                                               \
  _m("FAIL", __FILE__, __LINE__, __VA_ARGS__), cleanup(), exit(1);
#define warn(...) _m("WARN", __FILE__, __LINE__, __VA_ARGS__)
#define msg(...) _m("OK", __FILE__, __LINE__, __VA_ARGS__)

static void _m(const char *t, const char *f, const int l, const char *fmt,
               ...) {
  va_list args;

  va_start(args, fmt);

  printf("[%s] (%s:%d) ", t, f, l);
  vprintf(fmt, args);
  printf("\n");

  va_end(args);
}

typedef struct {
  Window w;
  int ws; // the workspace id
  int x, y, width, height, border;
} client;

typedef struct {
  int i; // the index of the workspace
  int clients_len;
  client **clients;
  client *foc; // the focused client(window)
} workspace;

typedef struct {
  Display *d;        // display
  int s;             // screen id
  Window r;          // root window
  int width, height; // screen width and height

  int wscnt, curr; // workspaces count and currently shown
  workspace *ws;   // list of workspaces
} state;

typedef struct {
  Mask mask;
} config;

#endif // KIWI_H
