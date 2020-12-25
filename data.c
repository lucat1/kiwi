#include "data.h"
#include "config.h"
#include "kiwi.h"
#include "util.h"
#include <stdlib.h>
#include <xcb/xcb.h>

int desktop_count = 0;

// initializes a client struct
client_t *new_client(xcb_window_t w) {
#ifdef DEBUG
  if (get_client(w) != NULL)
    fail("attempted to initialize new client with an existing window %d", w);
#endif

  client_t *c = malloc(sizeof(client_t));
  c->window = w;
  c->split_ratio = SPLIT_RATIO;
  c->split_direction = SPLIT_DIRECTION;

  return c;
}

client_t *get_client(xcb_window_t w) {
  list_t *diter = desktops;
  while (diter != NULL) {
    desktop_t *desk = (desktop_t *)diter->value;
    list_t *citer = desk->clients;
    while (citer != NULL) {
      client_t *c = (client_t *)citer->value;
      if (c->window == w)
        return c;

      citer = citer->next;
    }

    diter = diter->next;
  }

  return NULL;
}

// initializes a desktop struct
desktop_t *new_desktop(layout_t l) {
  desktop_t *desk = malloc(sizeof(desktop_t));
  desk->i = desktop_count++;
  desk->layout = l;
  desk->clients = NULL;
  desk->focused = NULL;
  desk->focus_stack = NULL;

  return desk;
}

void free_desktop(desktop_t *list) { stack_free(list->focus_stack); }
