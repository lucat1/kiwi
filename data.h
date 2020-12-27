#ifndef DATA_H
#define DATA_H

#include "list.h"
#include "stack.h"
#include <stdbool.h>
#include <xcb/randr.h>
#include <xcb/xcb.h>

typedef struct client client_t;
typedef struct layout layout_t;
typedef struct desktop desktop_t;
typedef struct monitor monitor_t;
typedef struct keybind keybind_t;
typedef struct handler_func handler_func_t;

enum split_direction { SPLIT_VERTICAL, SPLIT_HORIZONTAL };
enum visibility { SHOWN, HIDDEN };
enum motion_type { MOTION_NONE, MOTION_DRAGGING, MOTION_RESIZING };

struct client {
  xcb_window_t window;
  float split_ratio;
  enum split_direction split_direction;
  enum motion_type motion;
  enum visibility visibility;
  int16_t x, y;
  uint16_t w, h;
};

enum layout_type { LAYOUT_TILING, LAYOUT_FLOATING };

struct layout {
  enum layout_type type;

  void (*reposition)(desktop_t *d);

  void (*move_left)(desktop_t *d);
  void (*move_right)(desktop_t *d);
  void (*move_bottom)(desktop_t *d);
  void (*move_top)(desktop_t *d);
};

struct desktop {
  int i;

  layout_t layout;
  client_t *focused;

  list_t *clients;
  stack_t *focus_stack;
};

struct monitor {
  xcb_randr_output_t monitor;
  char *name;
  int16_t x, y;
  uint16_t w, h;
  desktop_t *focused;
  list_t *desktops;
};

struct arg {
  const int i;
  const char **v;
};

#define FN_ARG const struct arg

struct keybind {
  unsigned int mod;
  xcb_keysym_t keysym;
  void (*func)(FN_ARG arg);
  FN_ARG arg;
};

struct handler_func {
  uint32_t request;
  void (*func)(xcb_generic_event_t *ev);
};

extern int desktop_count;
client_t *new_client(xcb_window_t w);
client_t *get_client(xcb_window_t w);
desktop_t *new_desktop(layout_t l);
desktop_t *get_desktop(int i);
void free_desktop(desktop_t *list);
monitor_t *new_monitor(xcb_randr_output_t monitor, char *name, int16_t x,
                       int16_t y, uint16_t w, uint16_t h);
monitor_t *get_monitor(desktop_t *desk);
monitor_t *get_monitor_by_id(xcb_randr_output_t m);
monitor_t *get_monitor_clones(xcb_randr_output_t m, int16_t x, int16_t y);

#endif // DATA_H
