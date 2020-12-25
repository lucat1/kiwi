#include "layouts.h"
#include "config.h"
#include "data.h"
#include "kiwi.h"
#include "list.h"
#include "util.h"

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
  int i = 0, x = 0, y = 0, w = scr->width_in_pixels, h = scr->height_in_pixels;
  const bw = BORDER_WIDTH * 2;
  list_t *iter = desk->clients;
  while (iter != NULL) {
    bool fill = i == list_size(desk->clients) - 1;
    int width, height;
    client_t *c = (client_t *)iter->value;

    if (i == 0) {
      // drawing the main window
      width = (fill ? w : w * c->split_ratio) - bw;
      height = h - bw;
    } else {
      // drawing any seconday windows
      width = w - bw;
      height = (fill ? h : h * c->split_ratio) - bw;
    }

    move_resize_client(c, x, y, width, height);

    if (i == 0) {
      w -= width + bw;
      x = width + bw;
    } else {
      h -= height + bw;
      y += height + bw;
    }

    i++;
    iter = iter->next;
  }
}
