/* See LICENSE file for copyright and license details. */
#ifndef KIWI_H
#define KIWI_H

#include "data.h"
#include "list.h"
#include <stdbool.h>
#include <xcb/xcb_keysyms.h>

extern list_t *desktops;      // list of desktops
extern desktop_t *focdesk;    // the currently focused desktop
extern xcb_connection_t *dpy; // the X display
extern xcb_screen_t *scr;     // the X screen (TODO: xinerama)

/* user defined command actions */
void killclient(FN_ARG arg);
void spawn(FN_ARG arg);
void closewm(FN_ARG arg);
void send_to(FN_ARG arg);
void send_rel(FN_ARG arg);
void move_to(FN_ARG arg);
void move_rel(FN_ARG arg);

/* window behavior */
void focus_client(client_t *c);
void move_client(client_t *c, int16_t x, int16_t y, bool save);
void resize_client(client_t *c, uint16_t width, uint16_t height);
void hide_client(client_t *c);
void show_client(client_t *c);
void focus_desktop(desktop_t *desk);
void send_client(client_t *c, int i);
void setWindowDimensions(xcb_drawable_t window);
void setWindowPosition(xcb_drawable_t window);
void setBorderWidth(xcb_drawable_t window);
void setBorderColor(xcb_drawable_t window, int focus);

#endif
