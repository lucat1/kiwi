#include <xcb/xcb.h>

#include "client.h"
#include "desktop.h"
#include "kiwi.h"
#include "util.h"
#include "vec.h"

// array of all open clients
vec_t(client_t *) clients;

client_t *client_from_window(xcb_window_t win) {
  size_t i;

  for (i = 0; i < vec_size(clients); i++)
    if (clients[i] && clients[i]->window == win)
      return clients[i];

  return NULL;
}

void client_create(xcb_window_t win) {
  client_t *c;

  c = calloc(1, sizeof(client_t));
  if (c == NULL)
    die("could not allocate memory for new client");

  c->window = win;
  c->desktop = active_desktop;

  // gather the geometry for the window
  xcb_get_geometry_reply_t *g = xcb_gather_geometry(c->window);
  c->x = g->x;
  c->y = g->y;
  c->width = g->width;
  c->height = g->height;
  free(g);

  // add it to the array of clients
  vec_push(clients, c);
  msg("added client(%i) to desktop %i [x: %i, y: %i, w: %i, h: %i]", c->window,
      c->desktop, c->x, c->y, c->width, c->height);

  // add event listeners
  xcb_grab_button(conn, false, c->window, XCB_EVENT_MASK_BUTTON_PRESS,
                  XCB_GRAB_MODE_SYNC, XCB_GRAB_MODE_ASYNC, XCB_WINDOW_NONE,
                  XCB_CURSOR_NONE, XCB_BUTTON_INDEX_ANY, XCB_BUTTON_MASK_ANY);
}

void client_focus(client_t *client) {
  desktop_curr->focus = client;
  msg("focused client %p(%i)", client, client->window);

  xcb_set_input_focus(conn, XCB_INPUT_FOCUS_POINTER_ROOT, client->window,
                      XCB_CURRENT_TIME);
  xcb_raise_window(conn, client->window);
}
