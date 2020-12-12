#ifndef DATA_H
#define DATA_H

#include <xcb/xcb.h>

typedef struct client {
  xcb_window_t *window;
  unsigned int x, y, width, height;

  struct client *next;
} client_t;

typedef struct desktop {
  int i;

  client_t *clients;
} desktop_t;

#endif // DATA_H
