#include "layouts.h"
#include "config.h"
#include "data.h"
#include "kiwi.h"
#include "list.h"
#include "util.h"

static void tiling_reposition(desktop_t *desk);
static void floating_reposition(desktop_t *desk);

const layout_t tiling_layout = {.type = LAYOUT_TILING,
                                .reposition = tiling_reposition};
const layout_t floating_layout = {.type = LAYOUT_FLOATING,
                                  .reposition = floating_reposition};

// just shows hidden windows as they are moved manually by the user
static void floating_reposition(desktop_t *desk) {
  for (list_t *iter = desk->clients; iter != NULL; iter = iter->next) {
    client_t *c = iter->value;
    if (!c->mapped)
      continue;

    // restore its previous position
    move_client(c, c->x, c->y, false);

    if (c->visibility == HIDDEN)
      show_client(c);
  }
}

// checks whether there is any following client to be drawn and returns true if
// there are none (which means the current one should fill all the remaining
// space)
static bool should_fill(list_t *iter) {
  while (iter != NULL) {
    client_t *c = iter->value;
    if (c->mapped)
      return false;

    iter = iter->next;
  }

  return true;
}

// returns the first client in the list whwich is mapped
static client_t *first_mapped(list_t *iter) {
  while (iter != NULL) {
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

    move_resize_client(c, mon->x + x, mon->y + y, width, height);

    if (c == first) {
      w -= width + bw;
      x = width + bw;
    } else {
      h -= height + bw;
      y += height + bw;
    }
  }
}
