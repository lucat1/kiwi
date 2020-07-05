#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MOD Mod4Mask

#define die(...)                                                               \
  _m("FAIL", __FILE__, __LINE__, __VA_ARGS__), cleanup(), exit(1);
#define msg(...) _m("OK", __FILE__, __LINE__, __VA_ARGS__)

static void _m(const char *t, const char *f, const int l, const char *fmt,
               ...) {
  va_list args;

  va_start(args, fmt);

  printf("[%s] (%s:%d) ", t, f, l);
  vprintf(fmt, args);
  printf("\n");

  va_end(args);
}

typedef struct {
  int i;
  Window *windows;
} workspace;

typedef struct {
  Display *d; // display
  int s;      // screen id
  Window r;   // root window

  int wscnt, curr; // workspaces count and currently shown
  workspace *ws;
} state;

static state *wm;

static int xerror() { return 0; }

static void cleanup() {
  if (wm == NULL)
    return;

  // free any workspace
  if (wm->ws != NULL)
    free(wm->ws);

  free(wm);
}

static void ws_sel(int i) { wm->curr = i; }

static workspace *ws_add() {
  workspace *ws;
  if ((ws = calloc(0, sizeof(workspace))) == NULL)
    die("Cannot allocate memory for a new workspace");

  ws->i = wm->wscnt++;

  // expand the ws array in wm and add the new workspace to it
  // NOTE: we wanna check if the array has been initialized first tough
  //  as this might be the first workspace we add
  if (wm->ws == NULL && (wm->ws = calloc(0, sizeof(workspace *))) == NULL) {
    die("Cannot initialize the workspaces array");
  } else if ((wm->ws = realloc(wm->ws, (sizeof(workspace *)) * wm->wscnt)) ==
             NULL) {
    die("Cannot increase array of workspaces");
  }

  wm->ws[ws->i] = *ws;
  return ws;
}

void grab_mouse() {
  unsigned int i, j, modifiers[] = {0, LockMask, 0, 0 | LockMask};

  for (i = 1; i < 4; i += 2)
    for (j = 0; j < sizeof(modifiers) / sizeof(*modifiers); j++)
      XGrabButton(wm->d, i, MOD | modifiers[j], wm->r, True,
                  ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                  GrabModeAsync, GrabModeAsync, None, None);
}

Window get_top_level(Display *display, Window start) {
  Window root = None, parent, curr = start;
  Window *children;
  unsigned int nchildren;
  Status st;

  while (curr && curr != None && curr != root) {
    st = XQueryTree(display, curr, &root, &parent, &children, &nchildren);
    if (!st) {
      return None;
    }
    XFree(children);

    if (root == parent) {
      return curr;
    }
    curr = parent;
  }

  return None;
}

int main(void) {
  XWindowAttributes attr;
  XButtonEvent start;
  XEvent ev;
  Window foc;

  if ((wm = calloc(0, sizeof wm)) == NULL)
    die("Could not allocate memory for the wm struct");

  // Exit if display doesn't instantiate
  if (!(wm->d = XOpenDisplay(0x0)))
    die("Could not open the Xorg display");

  wm->wscnt = wm->curr = 0;
  wm->s = DefaultScreen(wm->d);
  wm->r = RootWindow(wm->d, wm->s);

  // instantiate at least one workspace
  ws_add();

  grab_mouse();

  start.subwindow = None;

  // Infinite loop
  for (;;) {

    XSetErrorHandler(xerror);
    XNextEvent(wm->d, &ev);
    /* XGetInputFocus(display, &foc, &revert_to); */
    foc = get_top_level(wm->d, ev.xkey.subwindow);
    XSync(wm->d, False);
    XSetInputFocus(wm->d, PointerRoot, RevertToPointerRoot, CurrentTime);
    // provide a default cursor
    XDefineCursor(wm->d, wm->s, XCreateFontCursor(wm->d, 68));

    if (ev.type == KeyPress && ev.xkey.subwindow != None) {

      // Close window with mod+q
      if (ev.xkey.keycode == XKeysymToKeycode(wm->d, XStringToKeysym("q"))) {
        XDestroyWindow(wm->d, foc);
      }

      // Lower windows with mod+a
      else if (ev.xkey.keycode ==
               XKeysymToKeycode(wm->d, XStringToKeysym("a"))) {
        XLowerWindow(wm->d, foc);
      }

      // Raise windows with mod+s
      else if (ev.xkey.keycode ==
               XKeysymToKeycode(wm->d, XStringToKeysym("s"))) {
        XRaiseWindow(wm->d, foc);
      }
    }

    if (ev.type == KeyPress) {
      // Open simple terminal with mod+return
      if (ev.xkey.keycode ==
          XKeysymToKeycode(wm->d, XStringToKeysym("Return"))) {
        system("alacritty &");
      }

      // Open dmenu with mod+d
      if (ev.xkey.keycode == XKeysymToKeycode(wm->d, XStringToKeysym("d"))) {
        system("dmenu_run");
      }

      // Close aphelia with mod+backspace
      else if (ev.xkey.keycode ==
               XKeysymToKeycode(wm->d, XStringToKeysym("BackSpace"))) {
        XCloseDisplay(wm->d);
      }
    }

    if (ev.type == ButtonPress && ev.xbutton.subwindow != None) {

      XGetWindowAttributes(wm->d, ev.xbutton.subwindow, &attr);
      XSetInputFocus(wm->d, ev.xbutton.subwindow, RevertToParent, CurrentTime);
      start = ev.xbutton;
    }

    else if (ev.type == MotionNotify && start.subwindow != None) {

      int xdiff = ev.xbutton.x_root - start.x_root;
      int ydiff = ev.xbutton.y_root - start.y_root;

      XMoveResizeWindow(wm->d, start.subwindow,
                        attr.x + (start.button == 1 ? xdiff : 0),
                        attr.y + (start.button == 1 ? ydiff : 0),

                        MAX(100, attr.width + (start.button == 3 ? xdiff : 0)),
                        MAX(50, attr.height + (start.button == 3 ? ydiff : 0)));
    }

    else if (ev.type == ButtonRelease) {

      start.subwindow = None;
    }
  }

  cleanup();
}
