#ifndef KIWI_H
#define KIWI_H

#include <stdbool.h>
#include <xcb/randr.h>
#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>

typedef struct list list_t;
typedef struct lifo lifo_t;

struct list {
  void *value;
  struct list *next;
};

struct lifo {
  void *value;
  struct lifo *prev;
};

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

enum layout_type { LAYOUT_TILING, LAYOUT_FLOATING };

struct layout {
  enum layout_type type;

  void (*reposition)(desktop_t *d);
  void (*motion)(rel_pointer_t p, client_t *c, monitor_t *mon);
  void (*move)(enum direction d, client_t *c, desktop_t *desk);
};

struct client {
  xcb_window_t window;
  float split_ratio;
  enum motion_type motion;
  enum visibility visibility;

  xcb_window_t decour;
  xcb_gcontext_t decour_gc;
  xcb_pixmap_t decour_pixmap;
  uint32_t decour_color, prev_decour_color;

  int16_t x, y, floating_x, floating_y, tiling_x, tiling_y, decour_x, decour_y;
  uint16_t w, h, floating_w, floating_h, tiling_w, tiling_h, decour_w, decour_h;
};

struct desktop {
  int i;

  layout_t layout;
  client_t *focused;

  list_t *clients;
  lifo_t *focus_stack;
};

struct monitor {
  xcb_randr_output_t monitor;
  const char *name;
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

void list_append(list_t **l, void *ele);
void list_remove(list_t **l, void *ele);
void list_free(list_t *l, void (*free)(void *));
int list_size(list_t *l);

void stack_push(lifo_t **s, void *ele);
void *stack_pop(lifo_t **s);
void stack_remove(lifo_t **s, void *ele);
void stack_free(lifo_t *s);

// data operations
client_t *new_client(xcb_window_t w);
client_t *get_client(xcb_window_t w);
desktop_t *new_desktop(layout_t l);
desktop_t *get_desktop(int i);
void free_desktop(desktop_t *list);
monitor_t *new_monitor(xcb_randr_output_t monitor, const char *name, int16_t x,
                       int16_t y, uint16_t w, uint16_t h);
monitor_t *get_monitor_for_desktop(desktop_t *desk);
monitor_t *get_monitor_for_client(client_t *c);
monitor_t *get_monitor_by_id(xcb_randr_output_t m);
monitor_t *get_monitor_by_coords(int16_t x, int16_t y);
monitor_t *get_monitor_clones(xcb_randr_output_t m, int16_t x, int16_t y);

// actions for keybinds
void killclient(FN_ARG arg);
void spawn(FN_ARG arg);
void closewm(FN_ARG arg);
void send_to(FN_ARG arg);
void send_rel(FN_ARG arg);
void move_to(FN_ARG arg);
void move_rel(FN_ARG arg);
void set_layout(FN_ARG arg);
void move(FN_ARG arg);

// client actions (internals)
void focus_client(client_t *c);
void move_client(client_t *c, int16_t x, int16_t y);
void resize_client(client_t *c, uint16_t width, uint16_t height);
void move_resize_client(client_t *c, int16_t x, int16_t y, uint16_t width,
                        uint16_t height);
void save_client(client_t *c, enum layout_type t);
void toggle_window(xcb_window_t win, enum visibility v);
void hide_client(client_t *c);
void show_client(client_t *c);
void new_decour(client_t *c);
void decorate_client(client_t *c);
void fit_client(client_t *c, monitor_t *mon);
void focus_desktop(desktop_t *desk);
void focus_monitor(monitor_t *mon);
void send_client(client_t *c, int i);
void setup_desktops(monitor_t *mon);

extern const layout_t floating_layout;
extern const layout_t tiling_layout;

#include "config.h"

#endif // KIWI_H

// vim: set foldmethod=marker foldmarker={{{,}}}:
