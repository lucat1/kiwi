#ifndef DESKTOP_H
#define DESKTOP_H

#include "client.h"
#include "vec.h"

typedef struct {
  int id;          // the (virtual) desktop id
  client_t *focus; // the focused client
} desktop_t;

vec_t(desktop_t *) desktops;
size_t active_desktop;

#define desktop_curr desktops[active_desktop]
void desktop_add();
void ws_delete(size_t ws);
void ws_focus(size_t ws);
vec_t(client_t *) clients_from_ws(size_t ws);

#endif // DESKTOP_H
