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

static void (*events[XCB_NO_OPERATION])(xcb_generic_event_t *e) = {
    [XCB_MAP_REQUEST] = handle_map_request,
    [XCB_DESTROY_NOTIFY] = handle_destroy_notify,
    [XCB_BUTTON_PRESS] = handle_button_press,
    [XCB_MOTION_NOTIFY] = handle_motion_notify,
    [XCB_BUTTON_RELEASE] = handle_button_release,

    [XCB_ENTER_NOTIFY] = handle_enter_notify,
    [XCB_LEAVE_NOTIFY] = handle_leave_notify,

    [XCB_FOCUS_IN] = handle_focus_in,
    [XCB_FOCUS_OUT] = handle_focus_out,

    [XCB_KEY_PRESS] = handle_key_press,
};
#endif // EVENTS_H
