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
  c->motion = MOTION_NONE;

  xcb_get_geometry_reply_t *geom = xcb_geometry(dpy, w);
  c->x = (scr->width_in_pixels - geom->width) / 2;
  c->y = (scr->height_in_pixels - geom->height) / 2;
  c->w = geom->width;
  c->h = geom->height;

  free(geom);
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

desktop_t *get_desktop(int i) {
  list_t *diter = desktops;
  while (diter != NULL) {
    desktop_t *desk = (desktop_t *)diter->value;
    if (desk->i == i)
      return desk;

    diter = diter->next;
  }

  return NULL;
}

void free_desktop(desktop_t *list) { stack_free(list->focus_stack); }
