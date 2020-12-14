/* See LICENSE file for copyright and license details. */
#ifndef KIWI_H
#define KIWI_H

#include "data.h"
#include <xcb/xcb_keysyms.h>

static desktop_t *kiwi_desktops;
static xcb_connection_t *dpy; // the X display
static xcb_screen_t *scr;

/* user defined command actions */
static void killclient(char **com);
static void spawn(char **com);
static void closewm(char **com);

/* window behavior */
static void setFocus(xcb_drawable_t window);
static void setWindowDimensions(xcb_drawable_t window);
static void setWindowPosition(xcb_drawable_t window);
static void setBorderWidth(xcb_drawable_t window);
static void setBorderColor(xcb_drawable_t window, int focus);

#endif
