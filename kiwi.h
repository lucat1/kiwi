/* See LICENSE file for copyright and license details. */
#ifndef KIWI_H
#define KIWI_H

#include <xcb/xcb_keysyms.h>

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
