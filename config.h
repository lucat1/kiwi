#ifndef CONFIG_H
#define CONFIG_H

#include "layouts.h"

#include "data.h"
#include "kiwi.h"
#include <X11/keysym.h>
#include <xcb/xcb_keysyms.h>

#define MODKEY XCB_MOD_MASK_4

// defines the default layout for new desktops
// options:
// - tiling_layout
// - floating_layout
#define DEFAULT_LAYOUT tiling_layout

/* DEFAULT WINDOW PROPERTIES
 * The following parameters can be used to change existing and new
 * window behavior.
 */

#define WINDOW_X 600
#define WINDOW_Y 400
#define WINDOW_MIN_X 60
#define WINDOW_MIN_Y 40
#define BORDER_WIDTH 1                  /* 0 = no border effect */
#define BORDER_COLOR_UNFOCUSED 0x696969 /* 0xRRGGBB */
#define BORDER_COLOR_FOCUSED 0xFFFFFF   /* 0xRRGGBB */

/* ALIASED COMMANDS
 * Each space delimited argument should be passed as an additional
 * value to the character pointer array. For example, to run
 * "foo -a bar", the array would be "{ "foo", "-a", "bar", NULL }".
 * Since execvp() is a variadic functions, each argument pointer must
 * be terminated by a NULL pointer.
 */

static char *termcmd[] = {"st", NULL};
static char *menucmd[] = {"dmenu_run", NULL};

/* KEY ALIASES
 * In general, one shortcut key should exist per alias. For more key
 * definitions, refer to the keysymdef.h and XF86keysym.h headers.
 */

static kiwi_key_t keys[] = {{MODKEY, XK_Return, spawn, termcmd},
                            {MODKEY, XK_space, spawn, menucmd},
                            {MODKEY, XK_w, killclient, NULL},
                            {MODKEY | XCB_MOD_MASK_SHIFT, XK_q, closewm, NULL}};

#endif // CONFIG_H
