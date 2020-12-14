#ifndef EVENTS_H
#define EVENTS_H

#include "data.h"
#include <X11/Xlib.h>
#include <xcb/xcb.h>

void handle_map_request(xcb_generic_event_t *ev);
void handle_destroy_notify(xcb_generic_event_t *ev);

void handle_button_press(xcb_generic_event_t *ev);
void handle_motion_notify(xcb_generic_event_t *ev);
void handle_button_release(xcb_generic_event_t *ev);

void handle_enter_notify(xcb_generic_event_t *ev);
void handle_leave_notify(xcb_generic_event_t *ev);

void handle_focus_in(xcb_generic_event_t *ev);
void handle_focus_out(xcb_generic_event_t *ev);

void handle_key_press(xcb_generic_event_t *ev);

extern void (*events[XCB_NO_OPERATION])(xcb_generic_event_t *e);

#endif // EVENTS_H
