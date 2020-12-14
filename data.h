#ifndef DATA_H
#define DATA_H

#include <xcb/xcb.h>

typedef struct client client_t;
typedef struct layout layout_t;
typedef struct desktop desktop_t;
typedef struct kiwi_key kiwi_key_t;
typedef struct handler_func handler_func_t;

struct client {
  xcb_window_t *window;
  unsigned int x, y, width, height;

  struct client *next;
};

enum layout_type { LAYOUT_TILING, LAYOUT_FLOATING };

struct layout {
  enum layout_type type;

  void (*move_left)(desktop_t *d);
  void (*move_right)(desktop_t *d);
  void (*move_bottom)(desktop_t *d);
  void (*move_top)(desktop_t *d);

  void (*send_left)(desktop_t *d);
  void (*send_right)(desktop_t *d);
  void (*send_bottom)(desktop_t *d);
  void (*send_top)(desktop_t *d);
};

struct desktop {
  int i;

  layout_t layout;
  client_t *clients;
  client_t *focused;

  struct desktop *next;
};

struct kiwi_key {
  unsigned int mod;
  xcb_keysym_t keysym;
  void (*func)(char **com);
  char **com;
};

struct handler_func {
  uint32_t request;
  void (*func)(xcb_generic_event_t *ev);
};

static desktop_t *kiwi_desktops;
static xcb_connection_t *dpy; // the X display
static xcb_screen_t *scr;

#endif // DATA_H
