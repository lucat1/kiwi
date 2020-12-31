/* See LICENSE file for copyright and license details. */
#ifndef KIWI_H
#define KIWI_H

#include "data.h"
#include "list.h"
#include <stdbool.h>
#include <xcb/xcb_keysyms.h>

extern list_t *monitors;  // list of monitors
extern monitor_t *focmon; // the currently focused monitor
#define focdesk ((desktop_t *)focmon->focused)
/* extern list_t *desktops;      // list of desktops */
/* extern desktop_t *focdesk;    // the currently focused desktop */
extern xcb_connection_t *dpy; // the X display
extern xcb_screen_t *scr;     // the X screen

/* user defined command actions */
void killclient(FN_ARG arg);
void spawn(FN_ARG arg);
void closewm(FN_ARG arg);
void send_to(FN_ARG arg);
void send_rel(FN_ARG arg);
void move_to(FN_ARG arg);
void move_rel(FN_ARG arg);
void set_layout(FN_ARG arg);
void move(FN_ARG arg);

/* window behavior */
void focus_client(client_t *c);
void move_client(client_t *c, int16_t x, int16_t y);
void resize_client(client_t *c, uint16_t width, uint16_t height);
void move_resize_client(client_t *c, int16_t x, int16_t y, uint16_t width,
                        uint16_t height);
void save_client(client_t *c, enum layout_type t);
void hide_client(client_t *c);
void show_client(client_t *c);
void fit_client(client_t *c, monitor_t *mon);
void focus_desktop(desktop_t *desk);
void focus_monitor(monitor_t *mon);
void send_client(client_t *c, int i);
void border_color(client_t *c, enum focus_type f);
void border_width(client_t *c, int width);
void setup_desktops(monitor_t *mon);

#endif
