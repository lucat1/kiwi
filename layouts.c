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
  msg("CALLED");
  if (list_size(desk->clients) == 0)
    return;

  msg("repositioning %d windows", list_size(desk->clients));

  list_t *iter = desk->clients;
  while (iter->next != NULL) {
    client_t *c = (client_t *)iter->value;
    show_client(c);
    iter = iter->next;
  }
  show_client(iter->value);
}
