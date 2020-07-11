#include <stdio.h>
#include <stdlib.h>
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
    // node actions
    {"close", KiwicClose, False, 0},
    {"kill", KiwicKill, False, 0},

    // workspaces actions
    {"workspaces", KiwicWorkspaces, False, 1},
};

cmd get_cmd(char *name) {
  int i;

  for (i = 0; i < (int)(sizeof(cmds) / sizeof(cmd)); i++)
    if (strcmp(cmds[i].name, name) == 0)
      return cmds[i];

  return w_cmd;
}

void send_cmd(int argc, char **argv, cmd cmd) {
  int i;
  XEvent ev;

  memset(&ev, 0, sizeof ev);
  ev.xclient.type = ClientMessage;
  ev.xclient.window = r;
  ev.xclient.message_type = XInternAtom(d, KIWI_CLIENT_EVENT, False);
  ev.xclient.format = 32;

  ev.xclient.data.l[0] = cmd.cmd;
  if (cmd.argc)
    // fill data sets (with parsed long ints)
    for (i = 2; i < argc; i++) {
      ev.xclient.data.l[i - 1] = strtol(argv[i], NULL, 10);
    }

  XSendEvent(d, r, False, SubstructureRedirectMask, &ev);
  XSync(d, False);
}

int main(int argc, char **argv) {
  cmd cmd;

  if (argc < 2)
    die("usage: kiwic <command> [opts]");

  if ((cmd = get_cmd(argv[1])).cmd == w_cmd.cmd)
    die("Invalid command %s", argv[1]);

  int r_argc = argc - 2;
  if (cmd.argc != r_argc)
    die("Too %s arguments; expected %i, got %i",
        r_argc > cmd.argc ? "many" : "few", cmd.argc, r_argc);

  d = XOpenDisplay(NULL);
  if (!d)
    die("Cannot open display");

  r = DefaultRootWindow(d);

  send_cmd(argc, argv, cmd);

  XCloseDisplay(d);
}
