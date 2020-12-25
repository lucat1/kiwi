#include "layouts.h"
#include "data.h"
#include "kiwi.h"
#include "list.h"
#include "util.h"

static void tiling_reposition(desktop_t *desk);

const layout_t tiling_layout = {.type = LAYOUT_TILING,
                                .reposition = tiling_reposition};

// repositions the windows in the tiling style.
// the first windows is called the "main" window and is,
// positioned to the left,while all others "secondary"
// windows are stacked one upon the other to the right.
static void tiling_reposition(desktop_t *desk) {
  if (list_size(desk->clients) == 0)
    return;

  int i = 0, x = 0, y = 0, w = scr->width_in_pixels, h = scr->height_in_pixels;
  list_t *iter = desk->clients;
  msg("desktop %p(%d) has %d clients", desk, desk->i, list_size(iter));
  while (iter != NULL) {
    client_t *c = (client_t *)iter->value;
    if (i == 0) {
      // drawing the master window
      int width = w * c->split_ratio;
      int height = h;
      move_resize_client(c, x, y, width, height);
      w -= width;
      x = width;
    } else {
      // drawing child windows
      int width = w;
      int height = h * c->split_ratio;
      move_resize_client(c, x, y, width, height);
      h -= height;
      y += height;
    }

    i++;
    iter = iter->next;
  }
}
