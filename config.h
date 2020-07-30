#ifndef CONFIG_H
#define CONFIG_H

#include <xcb/xcb.h>

typedef struct {
  int *mouse_focus; // buttons that shift focus to another window
  int sloppy_focus; // sloppy focus aka focus follows mouse

  int border_size; // the widths of the window's border
} config_t;

// default configuration
int default_mouse_focus[] = {
    XCB_BUTTON_INDEX_1, /* left click */
    XCB_BUTTON_INDEX_3  /* right click */
};

config_t config = {
    .mouse_focus = default_mouse_focus,
    .sloppy_focus = false,
    .border_size = 2,
};

#endif
