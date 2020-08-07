#include <xcb/xcb.h>

#include "config.h"

// default configuration
int default_mouse_focus[] = {
    XCB_BUTTON_INDEX_1, /* left click */
    XCB_BUTTON_INDEX_3, /* right click */
    0                   /* array delimiter */
};

config_t config = {
    .desktops = 4,
    .sloppy_focus = false,
    .border_size = 2,
};
