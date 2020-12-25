#ifndef CONFIG_H
#define CONFIG_H

#include "data.h"
#include "kiwi.h"
#include "layouts.h"
#include <X11/keysym.h>
#include <xcb/xcb_keysyms.h>

#define MODKEY XCB_MOD_MASK_4

// defines the default layout for new desktops
// options:
// - tiling_layout (default)
// - floating_layout
#define DEFAULT_LAYOUT tiling_layout

// type of focus for windows. could be as follows
// (0) click to focus (default)
// (1) focus follows pointer
#define FOCUS_TYPE 0

// amount of default desktops to create when the wm starts up
// NOTE: must be >= 1
#define DEFAULT_DESKTOPS 1

// follow sent windows to their new desktops
#define FOLLOW_SEND 1

// creates the destination desktop if it doesn't exist
#define CREATE_DESKTOP_IF_NOT_EXISTS 1

// split ratio - how to divide the screen in tiling mode
#define SPLIT_RATIO .6f
// default split direction for new windows. could be as follows
// - SPLIT_VERTICAL
// - SPLIT_HORIZONTAL
#define SPLIT_DIRECTION SPLIT_VERTICAL

/* DEFAULT WINDOW PROPERTIES
 * The following parameters can be used to change existing and new
 * window behavior.
 */

#define WINDOW_X 600
#define WINDOW_Y 400
#define WINDOW_MIN_X 60
#define WINDOW_MIN_Y 40
#define BORDER_WIDTH 0                  /* 0 = no border effect */
#define BORDER_COLOR_UNFOCUSED 0x696969 /* 0xRRGGBB */
#define BORDER_COLOR_FOCUSED 0xFFFFFF   /* 0xRRGGBB */

/* ALIASED COMMANDS
 * Each space delimited argument should be passed as an additional
 * value to the character pointer array. For example, to run
 * "foo -a bar", the array would be "{ "foo", "-a", "bar", NULL }".
 * Since execvp() is a variadic functions, each argument pointer must
 * be terminated by a NULL pointer.
 */

static const char *termcmd[] = {"st", NULL};
static const char *menucmd[] = {"dmenu_run", NULL};

/* KEY ALIASES
 * In general, one shortcut key should exist per alias. For more key
 * definitions, refer to the keysymdef.h and XF86keysym.h headers.
 */

#define WS(k, n)                                                               \
  {MODKEY, k, move_to, {.i = n}},                                              \
      {MODKEY | XCB_MOD_MASK_SHIFT, k, send_to, {.i = n}},
static keybind_t keys[] = {
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_space, spawn, {.v = menucmd}},
    {MODKEY, XK_w, killclient, NULL},

    {MODKEY, XK_l, move_rel, {.i = 1}},
    {MODKEY, XK_h, move_rel, {.i = -1}},
    {MODKEY | XCB_MOD_MASK_SHIFT, XK_l, send_rel, {.i = 1}},
    {MODKEY | XCB_MOD_MASK_SHIFT, XK_h, send_rel, {.i = -1}},

    WS(XK_1, 0) WS(XK_2, 1) WS(XK_3, 2) WS(XK_4, 3) WS(XK_5, 4)

        {MODKEY | XCB_MOD_MASK_SHIFT, XK_q, closewm, NULL},
};

#endif // CONFIG_H
