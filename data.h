#ifndef DATA_H
#define DATA_H

#include "stack.h"
#include <xcb/xcb.h>

typedef struct client client_t;
typedef struct layout layout_t;
typedef struct desktop desktop_t;
typedef struct keybind keybind_t;
typedef struct handler_func handler_func_t;

enum split_direction { SPLIT_VERTICAL, SPLIT_HORIZONTAL };

struct client {
  xcb_window_t window;
  float split_ratio;
  enum split_direction split_direction;

  struct client *next;
};

enum layout_type { LAYOUT_TILING, LAYOUT_FLOATING };

struct layout {
  enum layout_type type;

  void (*reposition)(desktop_t *d);

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

  stack_t *focus_stack;

  struct desktop *next;
};

struct keybind {
  unsigned int mod;
  xcb_keysym_t keysym;
  void (*func)(char **com);
  char **com;
};

struct handler_func {
  uint32_t request;
  void (*func)(xcb_generic_event_t *ev);
};

#define PUSHD(n, t) t *push_##n(t *head, t *n);
#define UNSHIFTD(n, t) t *unshift_##n(t *head, t *n);
#define REMOVED(n, t) t *remove_##n(t *iter, t *n);
#define FREED(n, t) void free_##n(t *list);
#define SIZED(n, t) int size_##n(t *list);

PUSHD(client, client_t)
UNSHIFTD(client, client_t)
REMOVED(client, client_t)
FREED(clients, client_t)
SIZED(clients, client_t)

PUSHD(desktop, desktop_t)
UNSHIFTD(desktop, desktop_t)
REMOVED(desktop, desktop_t)
FREED(desktops, desktop_t)
SIZED(desktops, desktop_t)

#undef PUSHD
#undef UNSHIFTD
#undef REMOVE
#undef PREPENDD
#undef FREED
#undef SIZED

client_t *new_client(xcb_window_t w);
client_t *get_client(xcb_window_t w);
desktop_t *new_desktop(layout_t l);

#endif // DATA_H
