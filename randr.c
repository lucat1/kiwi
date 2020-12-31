#include "randr.h"
#include "data.h"
#include "kiwi.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <xcb/randr.h>

// most of the code in this file is borrowed from the awesome windowchef

static void dummy_monitor();
static void get_outputs();

int randr_base = -1;

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
  monitor_t *mon;
  // update the existing monitor on resize
  if ((mon = get_monitor_by_id(0)) != NULL) {
    mon->w = scr->width_in_pixels;
    mon->h = scr->height_in_pixels;
    return;
  }
  mon = new_monitor(0, "dummy", 0, 0, scr->width_in_pixels,
                    scr->height_in_pixels);
  list_append(&monitors, mon);
  setup_desktops(mon);
}

void get_randr() {
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
  wm_info();
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

      monitor_t *mon;
      if ((mon = get_monitor_clones(outputs[i], crtc->x, crtc->y)) != NULL) {
        // when we have a clone always keep the one with the biggest resolution
        if (mon->w < crtc->width || mon->x < crtc->height)
          goto update;
      }

      mon = get_monitor_by_id(outputs[i]);
      if (mon == NULL) {
        monitor_t *monitor = new_monitor(outputs[i], name, crtc->x, crtc->y,
                                         crtc->width, crtc->height);
        list_append(&monitors, monitor);
        setup_desktops(monitor);
      } else {
        // update position if already available
        mon->x = crtc->x;
        mon->y = crtc->y;
      update:
        mon->w = crtc->width;
        mon->h = crtc->height;

        // reposition windows on the focused desktop
        if (mon->focused != NULL)
          mon->focused->layout.reposition(mon->focused);
      }

      free(crtc);
    } else {
      // Check if the monitor was used before
      // becoming disabled.
      monitor_t *mon = get_monitor_by_id(outputs[i]);
      if (mon != NULL) {
        // remove the monitor from the currently active ones
        list_remove(&monitors, mon);

        // die if no more monitors are available
        monitor_t *replacement;
        if (monitors == NULL || (replacement = monitors->value) == NULL)
          die("no more monitors remaining, could not display content");

        // move all clients to the new replacement desktop
        for (list_t *diter = mon->desktops; diter != NULL;
             diter = diter->next) {
          desktop_t *desk = diter->value;
          for (list_t *citer = desk->clients; citer != NULL;
               citer = citer->next) {
            list_append(&replacement->focused->clients, citer->value);
          }
        }

        list_free(mon->desktops, (void (*)(void *))free_desktop);
        free(mon);
      } else
        warn("removed unregistered monitor: %d", outputs[i]);
    }

    if (output != NULL)
      free(output);
    free(name);
  }
}
