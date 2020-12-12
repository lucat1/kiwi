#ifndef CONFIG_H
#define CONFIG_H

#include "kiwi.h"
#define XK_MISCELLANY
#define XK_XKB_KEYS
#include <X11/keysym.h>
#include <xcb/xcb_keysyms.h>

/* DEFAULT KEYS
 * The following are the possible mask definitions.  Note
 * that these definitions may vary between X implementations
 * and keyboard models.
 *     XCB_MOD_MASK_1       -> Alt_L Alt_R Meta_L
 *     XCB_MOD_MASK_2       -> Num_Lock
 *     XCB_MOD_MASK_3       -> ISO_Level3_Shift
 *     XCB_MOD_MASK_4       -> Super_L Super_R SuperL Hyper_L
 *     XCB_MOD_MASK_5       -> ISO_Level5_Shifta
 *     XCB_MOD_MASK_SHIFT
 *     XCB_MOD_MASK_CONTROL
 *     XCB_MOD_MASK_LOCK
 *     XCB_MOD_MASK_ANY
 */

#define MOD1 XCB_MOD_MASK_4
#define MOD2 XCB_MOD_MASK_SHIFT

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

static Key keys[] = {
    {MOD1, XK_Return, spawn, termcmd}, /* 0xff0d = XK_Enter */
    {MOD1, XK_space, spawn, menucmd},  /* 0x0020 = XK_space */
    {MOD1, XK_q, killclient, NULL},    /* 0x0071 = XK_q */
    {MOD1 | MOD2, XK_q, closewm, NULL} /* 0x0071 = XK_q */
};

#endif // CONFIG_H
