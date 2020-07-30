#include <xcb/xcb.h>

#include "client.h"
#include "kiwi.h"
#include "util.h"
#include "vector.h"
#include "workspace.h"

// array of all open clients
vec_t(client_t *) clients;

client_t *client_from_window(xcb_window_t win) {
  size_t i;

  for (i = 0; i < vec_size(clients); i++)
    if (clients[i] && clients[i]->win == win)
      return clients[i];

  return NULL;
}

void client_create(xcb_window_t win) {
  client_t *c;

  c = calloc(1, sizeof(client_t));
  if (c == NULL)
    die("could not allocate memory for new client");

  c->win = win;
  c->ws = active_ws;

  // gather the geometry for the window
  xcb_get_geometry_reply_t *g = xcb_gather_geometry(c->win);
  c->x = g->x;
  c->y = g->y;
  c->width = g->width;
  c->height = g->height;
  free(g);

  // add it to the array of clients
  vec_push(clients, c);
  msg("added client(%i) to workspace %i [x: %i, y: %i, w: %i, h: %i]", c->win,
      c->ws, c->x, c->y, c->width, c->height);

  // add event listeners
  xcb_grab_button(conn, false, win, XCB_EVENT_MASK_BUTTON_PRESS,
                  XCB_GRAB_MODE_SYNC, XCB_GRAB_MODE_ASYNC, XCB_WINDOW_NONE,
                  XCB_CURSOR_NONE, XCB_BUTTON_INDEX_ANY, XCB_BUTTON_MASK_ANY);
}
