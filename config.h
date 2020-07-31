#ifndef CONFIG_H
#define CONFIG_H

#include "util.h"

#include <xcb/xcb.h>

typedef struct {
  int *mouse_focus; // buttons that shift focus to another window
  int sloppy_focus; // sloppy focus aka focus follows mouse

  int border_size; // the widths of the window's border
} config_t;

config_t config;

#endif
