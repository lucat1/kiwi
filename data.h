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
typedef struct rel_pointer rel_pointer_t;
typedef struct handler_func handler_func_t;

enum visibility { SHOWN, HIDDEN };
enum motion_type { MOTION_NONE, MOTION_DRAGGING, MOTION_RESIZING };
enum focus_type { FOCUSED, FOCUSED_ANOTHER_MONITOR, UNFOCUSED };
enum direction {
  DIRECTION_LEFT,
  DIRECTION_RIGHT,
  DIRECTION_BOTTOM,
  DIRECTION_TOP
};

struct client {
  xcb_window_t window;
  float split_ratio;
  bool mapped;
  enum motion_type motion;
  enum visibility visibility;

  int16_t x, y;
  uint16_t w, h;

  int16_t actual_x, actual_y;
  uint16_t actual_w, actual_h;

  int16_t floating_x, floating_y;
  uint16_t floating_w, floating_h;
};

enum layout_type { LAYOUT_TILING, LAYOUT_FLOATING };

struct layout {
  enum layout_type type;

  void (*reposition)(desktop_t *d);
  void (*motion)(rel_pointer_t p, client_t *c, monitor_t *mon);
  void (*move)(enum direction d, client_t *c, desktop_t *desk);
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

struct rel_pointer {
  int16_t x, y;
};

struct arg {
  const int i;
  const char **v;
  const enum layout_type l;
  const enum direction d;
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
monitor_t *get_monitor_for_desktop(desktop_t *desk);
monitor_t *get_monitor_for_client(client_t *c);
monitor_t *get_monitor_by_id(xcb_randr_output_t m);
monitor_t *get_monitor_by_coords(int16_t x, int16_t y);
monitor_t *get_monitor_clones(xcb_randr_output_t m, int16_t x, int16_t y);

#endif // DATA_H
