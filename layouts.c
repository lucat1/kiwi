#include "layouts.h"
#include "data.h"
#include "list.h"

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

  list_t *c = desk->clients;
  while (c->next != NULL) {
    c = c->next;
  }

  /* c = c->next; */
}
