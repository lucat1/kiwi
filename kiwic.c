#include <stdio.h>
#include <string.h>

#include <X11/Xlib.h>

#include "kiwi.h"

typedef struct {
  char *name;
  enum kiwic_cmds cmd;
  int config; // true or false
  int argc;
} cmd;

static Display *d; // display
static Window r;   // root window

static cmd w_cmd = {"", KiwicLast, False, 0}; // wrong cmd; invalid
static cmd cmds[] = {
    {"close", KiwicClose, False, 0},
    {"kill", KiwicKill, False, 0},
};

cmd get_cmd(char *name) {
  int i;

  for (i = 0; i < (int)(sizeof(cmds) / sizeof(cmd)); i++)
    if (strcmp(cmds[i].name, name) == 0)
      return cmds[i];

  return w_cmd;
}

int main(int argc, char **argv) {
  XEvent ev;
  cmd cmd;

  if (argc < 2)
    die("usage: kiwic <command> [opts]");

  if ((cmd = get_cmd(argv[1])).cmd == w_cmd.cmd)
    die("Invalid command %s", argv[1]);

  d = XOpenDisplay(NULL);
  if (!d)
    die("Cannot open display");

  r = DefaultRootWindow(d);

  memset(&ev, 0, sizeof ev);
  ev.xclient.type = ClientMessage;
  ev.xclient.window = r;
  ev.xclient.message_type = XInternAtom(d, KIWI_CLIENT_EVENT, False);
  ev.xclient.format = 32;

  // TODO: config
  ev.xclient.data.l[0] = cmd.cmd;

  XSendEvent(d, r, False, SubstructureRedirectMask, &ev);
  XSync(d, False);
  XCloseDisplay(d);
}
