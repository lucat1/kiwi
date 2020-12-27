#include "data.h"
#include "config.h"
#include "kiwi.h"
#include "util.h"
#include <stdlib.h>
#include <xcb/randr.h>
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
  c->visibility = SHOWN;
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
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
      desktop_t *desk = diter->value;
      for (list_t *citer = desk->clients; citer != NULL; citer = citer->next) {
        client_t *c = (client_t *)citer->value;
        if (c->window == w)
          return c;
      }
    }
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
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
      desktop_t *desk = diter->value;
      if (desk->i == i)
        return desk;
    }
  }

  return NULL;
}

void free_desktop(desktop_t *list) { stack_free(list->focus_stack); }

monitor_t *new_monitor(xcb_randr_output_t monitor, char *name, int16_t x,
                       int16_t y, uint16_t w, uint16_t h) {
  monitor_t *mon = malloc(sizeof(monitor_t));
  mon->monitor = monitor;
  mon->name = name;
  mon->x = x;
  mon->y = y;
  mon->w = w;
  mon->h = h;
  return mon;
}

// returns the monitor which contains the requested desktop
monitor_t *get_monitor(desktop_t *desk) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
      desktop_t *desktop = diter->value;
      if (desktop == desk)
        return mon;
    }
  }
  return NULL;
}

// find a monitor in the mirror list by its xcb identifier
monitor_t *get_monitor_by_id(xcb_randr_output_t m) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    if (mon->monitor == m)
      return mon;
  }

  return NULL;
}

// find cloned (mirrored) outputs
monitor_t *get_monitor_clones(xcb_randr_output_t m, int16_t x, int16_t y) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    if (mon->monitor != m && mon->x == x && mon->y == y)
      return mon;
  }
  return NULL;
}
