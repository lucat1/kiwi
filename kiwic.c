#include <stdio.h>
#include <string.h>

#include <X11/Xlib.h>

#include "kiwi.h"

/* typedef struct { */
/*   char *name; */
/*   enum kiwic_cmds cmd; */
/*   int config; // true or false */
/*   int argc; */
/* } command; */

static Display *d; // display
static Window r;   // root window

int main(int argc, char *argv[]) {
  XEvent ev;

  d = XOpenDisplay(NULL);
  if (!d)
    die("Cannot open display");

  r = DefaultRootWindow(d);

  memset(&ev, 0, sizeof ev);
  ev.xclient.type = ClientMessage;
  ev.xclient.window = r;
  ev.xclient.message_type = XInternAtom(d, KIWI_CLIENT_EVENT, False);
  ev.xclient.format = 32;

  // TODO: config and arg parsing
  ev.xclient.data.l[0] = KiwicClose;

  XSendEvent(d, r, False, SubstructureRedirectMask, &ev);
  XSync(d, False);
  XCloseDisplay(d);
}
