#ifndef KIWI_H
#define KIWI_H

#include <xcb/xcb.h>

#include "config.h"

xcb_connection_t *conn;
xcb_screen_t *scr;
config_t config;

#endif // KIWI_H
