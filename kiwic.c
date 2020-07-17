#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

#include "kiwi.h"

typedef struct {
  char *name, *desc;
  enum kiwic_cmds cmd;
  int argc;
} cmd;

static Display *d; // display
static Window r;   // root window

static cmd w_cmd = {"", "", KiwicLast, 0}; // wrong cmd; invalid
static cmd cmds[] = {
    // node actions
    {"close", "Sends a close message to a window", KiwicClose, 0},
    {"kill", "Forcefully kills a window", KiwicKill, 0},

    // workspaces actions
    {"workspaces", "Sets the number of workspaces available", KiwicWorkspaces,
     1},
    {"focus_workspace", "Focuses the given workspace", KiwicFocusWorkspace, 1},
    {"send_to_workspace", "Sends a window to a workspace", KiwicSendToWorkspace,
     1},
};

// prints all available commands and adds a brief description to each
void help() {
  int i = 0, len = sizeof(cmds) / sizeof(cmd);

  printf("COMMANDS:\n\n");
  printf("%-22s argc desc\n", "cmd");
  for (; i < len; i++) {
    cmd cmd = cmds[i];
    printf("%-22s %-4i %s\n", cmd.name, cmd.argc, cmd.desc);
  }
}

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

  if (argc < 2) {
    printf("usage: kiwic <COMMAND> [args]\n");
    help();
    exit(1);
  }

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
