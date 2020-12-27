#include "data.h"
#include "kiwi.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <xcb/randr.h>

// most of the code in this file is borrowed from the awesome windowchef

static void dummy_monitor();
static void get_randr();
static void get_outputs();
static monitor_t *find_monitor(xcb_randr_output_t);
/* static monitor_t *find_monitor_by_coord(int16_t, int16_t); */
static monitor_t *find_clones(xcb_randr_output_t, int16_t, int16_t);

int randr_base;

void setup_randr() {
  const xcb_query_extension_reply_t *r =
      xcb_get_extension_data(dpy, &xcb_randr_id);

  if (!r->present) {
    dummy_monitor();
    return;
  }

  randr_base = r->first_event;
  get_randr();
  xcb_randr_select_input(dpy, scr->root,
                         XCB_RANDR_NOTIFY_MASK_SCREEN_CHANGE |
                             XCB_RANDR_NOTIFY_MASK_OUTPUT_CHANGE |
                             XCB_RANDR_NOTIFY_MASK_CRTC_CHANGE |
                             XCB_RANDR_NOTIFY_MASK_OUTPUT_PROPERTY);
}

// use a dummy monitor for when we can't identify monitors with randr
static void dummy_monitor() {
  monitor_t *mon = new_monitor(0, "dummy", 0, 0, scr->width_in_pixels,
                               scr->height_in_pixels);
  list_append(&monitors, mon);
}

static void get_randr() {
  xcb_randr_get_screen_resources_current_cookie_t c =
      xcb_randr_get_screen_resources_current(dpy, scr->root);
  xcb_randr_get_screen_resources_current_reply_t *r =
      xcb_randr_get_screen_resources_current_reply(dpy, c, NULL);

  if (r == NULL)
    fail("randr: could not fetch screen resources");

  xcb_timestamp_t timestamp = r->config_timestamp;
  int len = xcb_randr_get_screen_resources_current_outputs_length(r);
  xcb_randr_output_t *outputs =
      xcb_randr_get_screen_resources_current_outputs(r);

  if (len > 0)
    get_outputs(outputs, len, timestamp);
  else
    dummy_monitor();

  free(r);
}

static void get_outputs(xcb_randr_output_t *outputs, int len,
                        xcb_timestamp_t timestamp) {
  xcb_randr_get_output_info_cookie_t out_cookie[len];

  for (int i = 0; i < len; i++)
    out_cookie[i] = xcb_randr_get_output_info(dpy, outputs[i], timestamp);

  for (int i = 0; i < len; i++) {
    xcb_randr_get_output_info_reply_t *output =
        xcb_randr_get_output_info_reply(dpy, out_cookie[i], NULL);
    if (output == NULL)
      continue;

    int name_len = xcb_randr_get_output_info_name_length(output);
    if (16 < name_len)
      name_len = 16;

    char *name = malloc(name_len + 1);
    // make sure the name is at most name_len + 1 length
    // or we may run into problems.
    snprintf(name, name_len + 1, "%.*s", name_len,
             xcb_randr_get_output_info_name(output));

    if (output->crtc != XCB_NONE) {
      xcb_randr_get_crtc_info_cookie_t info_c =
          xcb_randr_get_crtc_info(dpy, output->crtc, timestamp);
      xcb_randr_get_crtc_info_reply_t *crtc =
          xcb_randr_get_crtc_info_reply(dpy, info_c, NULL);

      if (crtc == NULL)
        return;

      if (find_clones(outputs[i], crtc->x, crtc->y) != NULL)
        continue;

      monitor_t *mon = find_monitor(outputs[i]);
      if (mon == NULL) {
        monitor_t *monitor = new_monitor(outputs[i], name, crtc->x, crtc->y,
                                         crtc->width, crtc->height);
        list_append(&monitors, monitor);
      } else {
        // update position if already available
        mon->x = crtc->x;
        mon->y = crtc->y;
        mon->w = crtc->width;
        mon->h = crtc->height;

        // TODO: arrange?
        /* arrange_by_monitor(mon); */
      }

      free(crtc);
    } else {
      // Check if the monitor was used before
      // becoming disabled.
      monitor_t *mon = find_monitor(outputs[i]);
      if (mon != NULL) {
        // remove the monitor from the currently active ones
        list_remove(&monitors, mon);

        // die if no more monitors are available
        monitor_t *replacement;
        if (monitors == NULL || (replacement = monitors->value) == NULL)
          die("no more monitors remaining, could not display content");

        // move all desktops to the new replacement monitor
        for (list_t *diter = mon->desktops; diter != NULL;
             diter = diter->next) {
          list_append(&replacement->desktops, diter->value);
        }

        free(mon);
      }
    }

    if (output != NULL)
      free(output);
    free(name);
  }
}

/*
 * Finds a monitor in the list.
 */

static monitor_t *find_monitor(xcb_randr_output_t m) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    if (mon->monitor == m)
      return mon;
  }

  return NULL;
}

/*
 * Find a monitor in the list by its coordinates.
 */

/* static monitor_t *find_monitor_by_coord(int16_t x, int16_t y) { */
/*   monitor_t *res = NULL; */
/*   for (list_t *miter = monitors; miter != NULL; miter = miter->next) { */
/*     monitor_t *mon = miter->value; */
/*     if (x >= mon->x && x <= mon->x + mon->w && y >= mon->y && */
/*         y <= mon->y + mon->h) */
/*       res = mon; */
/*   } */
/*   return res; */
/* } */

/*
 * Find cloned (mirrored) outputs.
 */

static monitor_t *find_clones(xcb_randr_output_t m, int16_t x, int16_t y) {
  for (list_t *miter = monitors; miter != NULL; miter = miter->next) {
    monitor_t *mon = miter->value;
    if (mon->monitor != m && mon->x == x && mon->y == y)
      return mon;
  }
  return NULL;
}
