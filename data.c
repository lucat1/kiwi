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
  c->mapped = false;
  c->split_ratio = SPLIT_RATIO;
  c->split_direction = SPLIT_DIRECTION;
  c->visibility = HIDDEN;
  c->motion = MOTION_NONE;

  xcb_get_geometry_reply_t *geom = xcb_geometry(dpy, w);
  c->actual_x = c->x = c->floating_x = (focmon->w - geom->width) / 2;
  c->actual_y = c->y = c->floating_y = (focmon->h - geom->height) / 2;
  c->actual_w = c->w = c->floating_w = geom->width;
  c->actual_h = c->h = c->floating_h = geom->height;

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

void free_desktop(desktop_t *list) {
  stack_free(list->focus_stack);
  desktop_count--;
}

monitor_t *new_monitor(xcb_randr_output_t monitor, char *name, int16_t x,
                       int16_t y, uint16_t w, uint16_t h) {
  monitor_t *mon = malloc(sizeof(monitor_t));
  mon->monitor = monitor;
  mon->name = name;
  mon->x = x;
  mon->y = y;
  mon->w = w;
  mon->h = h;
  mon->focused = NULL;
  mon->desktops = NULL;
  return mon;
}

// returns the monitor which contains the requested desktop
monitor_t *get_monitor_for_desktop(desktop_t *desk) {
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

monitor_t *get_monitor_for_client(client_t *c) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    for (list_t *diter = mon->desktops; diter != NULL; diter = diter->next) {
      desktop_t *desk = diter->value;
      for (list_t *citer = desk->clients; citer != NULL; citer = citer->next) {
        client_t *client = citer->value;
        if (client == c)
          return mon;
      }
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

// find a monitor by its coordinates
monitor_t *get_monitor_by_coords(int16_t x, int16_t y) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    // mon->x < x < mon->x+mon->w
    // mon->y < y < mon->y+mon->h
    if ((x >= mon->x && x <= (mon->x + mon->w)) &&
        (y >= mon->y && y <= (mon->y + mon->h)))
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
