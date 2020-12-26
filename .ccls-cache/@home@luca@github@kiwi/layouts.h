#ifndef LAYOUTS_H
#define LAYOUTS_H

#include "data.h"

static void tiling_reposition(desktop_t *desk);
static void floating_reposition(desktop_t *desk);

extern const layout_t tiling_layout;
extern const layout_t floating_layout;

#endif // LAYOUTS_H
