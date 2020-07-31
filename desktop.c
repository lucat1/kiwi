#include "desktop.h"
#include "util.h"

vec_t(desktop_t *) desktops;
size_t active_desktop = 0;

void desktop_add() {
  size_t i = vec_size(desktops);
  desktop_t *desktop;

  if ((desktop = calloc(1, sizeof(desktop))) == NULL)
    die("could not allocate memory for desktop %lu", i);

  desktop->id = i;
  vec_push(desktops, desktop);

  msg("Added workspace %i", desktop->id);
}
