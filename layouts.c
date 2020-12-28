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
  list_t *iter = desk->clients;
  while (iter != NULL) {
    client_t *c = (client_t *)iter->value;
    if (c->visibility == HIDDEN)
      show_client(c);

    iter = iter->next;
  }
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
  for (list_t *iter = desk->clients; iter != NULL; iter = iter->next) {
    bool fill = iter->next == NULL;
    int width, height;
    client_t *c = (client_t *)iter->value;

    if (iter == desk->clients) {
      // drawing the main window
      width = (fill ? w : w * c->split_ratio) - bw;
      height = h - bw;
    } else {
      // drawing any seconday windows
      width = w - bw;
      height = (fill ? h : h * c->split_ratio) - bw;
    }

    // TODO: guess fix positioning inside move_resize_client itself
    move_resize_client(c, mon->x + x, mon->y + y, width, height);

    if (iter == desk->clients) {
      w -= width + bw;
      x = width + bw;
    } else {
      h -= height + bw;
      y += height + bw;
    }
  }
}
