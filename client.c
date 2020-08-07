#include <xcb/xcb.h>

#include "client.h"
#include "desktop.h"
#include "kiwi.h"
#include "util.h"
#include "vec.h"

// array of all open clients
vec_t(client_t *) clients = NULL;

client_t *client_from_window(xcb_window_t win) {
  size_t i;

  for (i = 0; i < vec_size(clients); i++)
    if (clients[i] && clients[i]->window == win)
      return clients[i];

  return NULL;
}

void client_create(xcb_window_t window) {
  size_t i;
  client_t *client;

  client = calloc(1, sizeof(client_t));
  if (client == NULL)
    die("could not allocate memory for new client");

  client->window = window;
  client->desktop = active_desktop;

  // gather the geometry for the window
  xcb_get_geometry_reply_t *g = xcb_gather_geometry(client->window);
  client->x = g->x;
  client->y = g->y;
  client->width = g->width;
  client->height = g->height;
  free(g);

  // add it to the array of clients
  vec_push(clients, client);
  msg("added client(%i) to desktop %i [x: %i, y: %i, w: %i, h: %i]",
      client->window, client->desktop, client->x, client->y, client->width,
      client->height);

  client_focus(client);

  // add event listeners
  for (i = 0; i < vec_size(config.mouse_focus); i++)
    xcb_grab_button(conn, false, client->window, XCB_EVENT_MASK_BUTTON_PRESS,
                    XCB_GRAB_MODE_SYNC, XCB_GRAB_MODE_ASYNC, XCB_WINDOW_NONE,
                    XCB_CURSOR_NONE, config.mouse_focus[i],
                    XCB_BUTTON_MASK_ANY);
}

void client_focus(client_t *client) {
  desktop_curr->focus = client;
  msg("focused client %p(%i)", client, client->window);

  xcb_set_input_focus(conn, XCB_INPUT_FOCUS_POINTER_ROOT, client->window,
                      XCB_CURRENT_TIME);
  xcb_raise_window(conn, client->window);
}

void client_move(client_t *client, int x, int y) {
  unsigned int pos[2] = {x, y};

  client->x = x;
  client->y = y;
  xcb_configure_window(conn, client->window, XCB_MOVE, pos);
}

void client_resize(client_t *client, int w, int h) {
  unsigned int pos[2] = {w, h};

  client->width = w;
  client->height = h;
  xcb_configure_window(conn, client->window, XCB_RESIZE, pos);
}
