#include "layouts.h"
#include "config.h"
#include "data.h"
#include "kiwi.h"
#include "list.h"
#include "util.h"

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

static void floating_reposition(desktop_t *desk);
static void floating_motion(rel_pointer_t *p, client_t *c, monitor_t *mon);
static void tiling_reposition(desktop_t *desk);
static void tiling_motion(rel_pointer_t *p, client_t *c, monitor_t *mon);

const layout_t floating_layout = {.type = LAYOUT_FLOATING,
                                  .reposition = floating_reposition,
                                  .motion = floating_motion};
const layout_t tiling_layout = {.type = LAYOUT_TILING,
                                .reposition = tiling_reposition,
                                .motion = tiling_motion};

// just shows hidden windows as they are moved manually by the user
static void floating_reposition(desktop_t *desk) {
  for (list_t *iter = desk->clients; iter != NULL; iter = iter->next) {
    client_t *c = iter->value;
    if (!c->mapped)
      continue;

    // restore its previous position
    move_resize_client(c, c->floating_x, c->floating_y, c->floating_w,
                       c->floating_h);

    if (c->visibility == HIDDEN)
      show_client(c);
  }
}

static void floating_motion(rel_pointer_t *p, client_t *c, monitor_t *mon) {
  UNUSED(mon);
  // TODO: take border into account
  if (c->motion == MOTION_DRAGGING) {
    // TODO: prevent window from exiting the screen (bottom left)
    int16_t x = MIN(mon->w - c->floating_w, MAX(c->floating_x + p->x, 0));
    int16_t y = MIN(mon->h - c->floating_h, MAX(c->floating_y + p->y, 0));
    move_client(c, x, y);
  } else if (c->motion == MOTION_RESIZING) {
    int16_t w =
        MIN(mon->w - c->floating_x, MAX(c->floating_w + p->x, MIN_WIDTH));
    int16_t h =
        MIN(mon->h - c->floating_y, MAX(c->floating_h + p->y, MIN_HEIGHT));
    resize_client(c, w, h);
  }
}

// checks whether there is any following client to be drawn and returns true if
// there are none (which means the current one should fill all the remaining
// space)
static bool should_fill(list_t *iter) {
  for (; iter != NULL; iter = iter->next) {
    client_t *c = iter->value;
    if (c->mapped)
      return false;
  }

  return true;
}

// returns the first client in the list whwich is mapped
static client_t *first_mapped(list_t *iter) {
  for (; iter != NULL; iter = iter->next) {
    client_t *c = iter->value;
    if (c->mapped)
      return c;
  }

  return NULL;
}

// repositions the windows in the tiling style.
// the first windows is called the "main" window and is,
// positioned to the left,while all others "secondary"
// windows to be stacked one upon the other to the right.
static void tiling_reposition(desktop_t *desk) {
  monitor_t *mon = get_monitor_for_desktop(desk);
  if (mon == NULL)
    fail("could not get monitor for desktop");

  int x = 0, y = 0, w = mon->w, h = mon->h;
  const int bw = BORDER_WIDTH * 2;
  client_t *first = first_mapped(desk->clients);
  for (list_t *iter = desk->clients; iter != NULL; iter = iter->next) {
    bool fill = should_fill(iter->next);
    int width, height;
    client_t *c = iter->value;
    if (c == NULL || !c->mapped)
      continue;

    if (c == first) {
      // drawing the main window
      width = (fill ? w : w * c->split_ratio) - bw;
      height = h - bw;
    } else {
      // drawing any seconday windows
      width = w - bw;
      height = (fill ? h : h * c->split_ratio) - bw;
    }

    move_resize_client(c, x, y, width, height);
    save_client(c, LAYOUT_TILING);

    if (c == first) {
      w -= width + bw;
      x = width + bw;
    } else {
      h -= height + bw;
      y += height + bw;
    }
  }
}

static void tiling_motion(rel_pointer_t *p, client_t *c, monitor_t *mon) {
  UNUSED(p);
  UNUSED(c);
  UNUSED(mon);
}
