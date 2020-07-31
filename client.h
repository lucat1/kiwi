#ifndef CLIENT_H
#define CLIENT_H

#include "vec.h"
#include <xcb/xcb.h>

typedef struct {
  int ws;           // the workspace the client belongs to
  xcb_window_t win; // the window for this client

  int x, y;          // window position
  int width, height; // window sizes
} client_t;

vec_t(client_t *) clients;

client_t *client_from_window(xcb_window_t win);
void client_create(xcb_window_t win);
void client_show(client_t *c);
void client_hide(client_t *c);
void client_focus(client_t *c);
void client_move(client_t *c, int x, int y);
void client_resize(client_t *c, int w, int h);
void client_border(client_t *c, char *color);
void client_close(client_t *c);
void client_kill(client_t *c);
void client_delete(client_t *c);

#endif // CLIENT_H
