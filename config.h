#ifndef CONFIG_H
#define CONFIG_H

#include "data.h"
#include "kiwi.h"
#include "layouts.h"
#include <X11/keysym.h>
#include <xcb/xcb_keysyms.h>

#define MODKEY XCB_MOD_MASK_4
#define SHIFT XCB_MOD_MASK_SHIFT

// defines the default layout for new desktops
// options:
// - tiling_layout
// - floating_layout (default)
#define DEFAULT_LAYOUT floating_layout

// type of focus for windows. could be as follows
// (0) click to focus (default)
// (1) focus follows pointer
#define FOCUS_TYPE 0

// amount of default desktops to create when the wm starts up
// NOTE: must be >= 1 (default: 5)
#define DEFAULT_DESKTOPS 2

// follow sent windows to their new desktops
#define FOLLOW_SEND 0

// creates the destination desktop if it doesn't exist
#define CREATE_DESKTOP_IF_NOT_EXISTS 1

// split ratio - how to divide the screen in tiling mode
#define SPLIT_RATIO .6f
// default split direction for new windows. could be as follows
// - SPLIT_VERTICAL
// - SPLIT_HORIZONTAL
#define SPLIT_DIRECTION SPLIT_VERTICAL

// the border around each window. can be set to 0 to remove
#define BORDER_WIDTH 1

// colors for window borders
#define BORDER_COLOR_UNFOCUSED 0x696969
#define BORDER_COLOR_FOCUSED 0xFFFFFF

// minimum window sizes to be held while resizing
#define MIN_WIDTH 60
#define MIN_HEIGHT 40

// amount of pixels to move the window by each step (with binds)
#define MOVE_STEP 25

// program commands, used later in bindings
static const char *termcmd[] = {"alacritty", NULL};
static const char *menucmd[] = {"dmenu_run", NULL};

#define WS(k, n)                                                               \
  {MODKEY, k, move_to, {.i = n}}, {                                            \
    MODKEY | XCB_MOD_MASK_SHIFT, k, send_to, { .i = n }                        \
  }
static const struct arg noarg = {0};

// keybinds
static const keybind_t keys[] = {
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_space, spawn, {.v = menucmd}},
    {MODKEY, XK_w, killclient, noarg},

    {MODKEY, XK_h, move, {.d = DIRECTION_LEFT}},
    {MODKEY, XK_j, move, {.d = DIRECTION_BOTTOM}},
    {MODKEY, XK_k, move, {.d = DIRECTION_TOP}},
    {MODKEY, XK_l, move, {.d = DIRECTION_RIGHT}},

    {MODKEY | SHIFT, XK_k, move_rel, {.i = 1}},
    {MODKEY | SHIFT, XK_j, move_rel, {.i = -1}},
    {MODKEY | SHIFT, XK_l, send_rel, {.i = 1}},
    {MODKEY | SHIFT, XK_h, send_rel, {.i = -1}},

    {MODKEY, XK_f, set_layout, {.l = LAYOUT_FLOATING}},
    {MODKEY, XK_t, set_layout, {.l = LAYOUT_TILING}},

    WS(XK_1, 0),
    WS(XK_2, 1),
    WS(XK_3, 2),
    WS(XK_4, 3),
    WS(XK_5, 4),

    {MODKEY | SHIFT, XK_q, closewm, noarg},
};

#endif // CONFIG_H
