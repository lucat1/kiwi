/* See LICENSE file for copyright and license details. */
#ifndef KIWI_H
#define KIWI_H

#include "data.h"
#include <xcb/xcb_keysyms.h>

extern desktop_t *desktops;        // list of desktops
extern desktop_t *focused_desktop; // the currently focused desktop
extern xcb_connection_t *dpy;      // the X display
extern xcb_screen_t *scr;          // the X screen (TODO: xinerama)

// TODO: remove me!!
extern xcb_window_t focused;

/* user defined command actions */
void killclient(char **com);
void spawn(char **com);
void closewm(char **com);

/* window behavior */
void setFocus(xcb_drawable_t window);
void setWindowDimensions(xcb_drawable_t window);
void setWindowPosition(xcb_drawable_t window);
void setBorderWidth(xcb_drawable_t window);
void setBorderColor(xcb_drawable_t window, int focus);

#endif
