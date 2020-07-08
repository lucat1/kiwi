#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MOUSEMASK (PointerMotionMask | ButtonPressMask | ButtonReleaseMask)
#define MAXLEN 256
#define AUTOSTART "kiwi/autostart"

#define die(...)                                                               \
  _m("FAIL", __FILE__, __LINE__, __VA_ARGS__), cleanup(), exit(1);
#define warn(...) _m("WARN", __FILE__, __LINE__, __VA_ARGS__)
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
  Window w;
  int ws; // the workspace id
  int x, y, width, height, border;
} client;

typedef struct {
  int i; // the index of the workspace
  int clients_len;
  client **clients;
  client *foc; // the focused client(window)
} workspace;

typedef struct {
  Display *d; // display
  int s;      // screen id
  Window r;   // root window

  int wscnt, curr; // workspaces count and currently shown
  workspace *ws;   // list of workspaces
} state;

typedef struct {
  int x, y;
  int width, height;
  int border;
} geometry;

typedef struct {
  Mask move_mask, resize_mask;
} config;

static workspace ws_curr();
static workspace *ws_add();

static void handle_map_request(XEvent *ev);
static void handle_button_press(XEvent *ev);

static void handle_new_window(Window w, XWindowAttributes *wa);

char cfgp[MAXLEN]; // path to config file
static state *wm;  // wm global state

static int clients_len = 0; // the length of the clients array
static client **clients; // list of available clients (wrapper around windows)
static config cfg = {Mod4Mask, Mod1Mask};

static Cursor move_cursor, normal_cursor;
static int (*xerrorxlib)(Display *, XErrorEvent *);

static void (*events[LASTEvent])(XEvent *e) = {
    [MapRequest] = handle_map_request,
    [ButtonPress] = handle_button_press,
};

static int xerror(Display *d, XErrorEvent *ee) {
  if (ee->error_code == BadWindow ||
      (ee->request_code == X_SetInputFocus && ee->error_code == BadMatch) ||
      (ee->request_code == X_PolyText8 && ee->error_code == BadDrawable) ||
      (ee->request_code == X_PolyFillRectangle &&
       ee->error_code == BadDrawable) ||
      (ee->request_code == X_PolySegment && ee->error_code == BadDrawable) ||
      (ee->request_code == X_ConfigureWindow && ee->error_code == BadMatch) ||
      (ee->request_code == X_GrabButton && ee->error_code == BadAccess) ||
      (ee->request_code == X_GrabKey && ee->error_code == BadAccess) ||
      (ee->request_code == X_CopyArea && ee->error_code == BadDrawable))
    return 0;

  fprintf(stderr, "dwm: fatal error: request code=%d, error code=%d\n",
          ee->request_code, ee->error_code);

  return xerrorxlib(d, ee); /* may call exit */
}

static void cleanup() {
  if (wm == NULL)
    return;

  // free any workspace
  if (wm->ws != NULL)
    free(wm->ws);

  if (clients != NULL && clients_len) {
    for (int i = 0; i < clients_len; i++)
      free(clients[i]);

    free(clients);
  }

  XCloseDisplay(wm->d);
  free(wm);
}

static int find_autostart() {
  char *xdg_home = getenv("XDG_CONFIG_HOME");
  if (xdg_home != NULL) {
    snprintf(cfgp, MAXLEN, "%s/%s", xdg_home, AUTOSTART);
  } else {
    char *home = getenv("HOME");
    if (home == NULL) {
      warn("$XDG_CONFIG_HOME and $HOME not found autostart will not be loaded");
      return 0;
    }

    snprintf(cfgp, MAXLEN, "%s/%s/%s", home, ".config", AUTOSTART);
  }

  return 1;
}

static void run_autostart() {
  if (fork() == 0) {
    setsid();
    execl("/bin/sh", "/bin/sh", cfgp, NULL);
    msg("Executed: %s", cfgp);
  }
}

static void client_add(client *c) {
  msg("added client(id: %lu, x: %i, y: %i, w: %i, h: %i)", c->w, c->x, c->y,
      c->width, c->height);
  clients_len++;

  // assign the needed memory
  if (clients == NULL && clients_len == 0) {
    if ((clients = calloc(0, sizeof(client *))) == NULL)
      die("Cannot initialize the clients array");
  } else {
    if ((clients = realloc(clients, sizeof(client *) * clients_len)) == NULL)
      die("Cannot increase array of clients");
  }

  clients[clients_len - 1] = c;

  workspace ws = ws_curr();
  ws.clients_len++;
  // add the client to the workspace list of clients
  if (ws.clients == NULL && clients_len == 0) {
    if ((clients = calloc(0, sizeof(client *))) == NULL)
      die("Cannot initialize the clients array");
  } else {
    if ((clients = realloc(clients, sizeof(client *) * clients_len)) == NULL)
      die("Cannot increase array of clients");
  }
}

static client *client_from_window(Window w) {
  for (int i = 0; i < clients_len; i++) {
    if (clients[i] != NULL && clients[i]->w == w)
      return clients[i];
  }

  return NULL;
}

static void client_move(client *c, int x, int y) {
  XMoveWindow(wm->d, c->w, x, y);

  c->x = x;
  c->y = y;
}

static void client_resize(client *c, int x, int y) {
  // TODO: resize
}

static void ws_sel(int i) { wm->curr = i; }
static workspace ws_curr() { return wm->ws[wm->curr]; }

static workspace *ws_add() {
  workspace *ws;
  if ((ws = calloc(0, sizeof(workspace))) == NULL)
    die("Cannot allocate memory for a new workspace");

  ws->i = wm->wscnt++;

  // expand the ws array in wm and add the new workspace to it
  // NOTE: we wanna check if the array has been initialized first tough
  //  as this might be the first workspace we add
  if (wm->ws == NULL && (wm->ws = calloc(0, sizeof(workspace))) == NULL) {
    die("Cannot initialize the workspaces array");
  } else if ((wm->ws = realloc(wm->ws, (sizeof(workspace)) * wm->wscnt)) ==
             NULL) {
    die("Cannot increase array of workspaces");
  }

  wm->ws[ws->i] = *ws;
  return ws;
}

static void ws_focus(client *c) {
  workspace ws;

  ws = ws_curr();
  ws.foc = c;

  XSetInputFocus(wm->d, c->w, RevertToPointerRoot, CurrentTime);
  XRaiseWindow(wm->d, c->w);
}

static void handle_map_request(XEvent *ev) {
  static XWindowAttributes wa;
  XMapRequestEvent *e = &ev->xmaprequest;

  if (!XGetWindowAttributes(wm->d, e->window, &wa)) {
    warn("Could not get window attributes (%d)", e->window);
    return;
  }

  if (wa.override_redirect)
    return;

  msg("Handling request map event");

  handle_new_window(e->window, &wa);
}

static void handle_new_window(Window w, XWindowAttributes *wa) {
  client *c;

  if (client_from_window(w) != NULL) {
    warn("Trying to rehandle as a new window: %d", w);
    return;
  }

  c = malloc(sizeof(client));
  if (c == NULL)
    die("Could not allocate memory for new client(window)");

  c->w = w;
  c->ws = ws_curr().i;
  c->x = wa->x;
  c->y = wa->y;
  c->width = wa->width;
  c->height = wa->height;
  c->border = wa->border_width;

  client_add(c);

  // resize the window(needed for some applications) and map it(display)
  XMoveResizeWindow(wm->d, c->w, c->x, c->y, c->width, c->height);
  XMapWindow(wm->d, c->w);

  // grab events
  XSelectInput(wm->d, c->w,
               EnterWindowMask | FocusChangeMask | PropertyChangeMask |
                   StructureNotifyMask);
  XGrabButton(wm->d, Button1, AnyModifier, c->w, True,
              ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
              GrabModeAsync, GrabModeAsync, None, None);

  ws_focus(c);
}

static void handle_button_press(XEvent *ev) {
  /* Much credit to the authors of dwm for
   * this function.
   */
  XButtonPressedEvent *bev = &ev->xbutton;
  XEvent e;
  client *c;
  int x, y, ocx, ocy, nx, ny, nw, nh, di, ocw, och;
  unsigned int dui;
  Window dummy;

  XQueryPointer(wm->d, wm->r, &dummy, &dummy, &x, &y, &di, &di, &dui);
  msg("Handling button press event");
  c = client_from_window(bev->window);
  if (c == NULL) {
    warn("Button click on unkown client (w: %d)", bev->window);
    return;
  }

  if (c != ws_curr().foc)
    ws_focus(c);

  // stop here if we don't have any modifier applied
  if (ev->xbutton.state == 0)
    return;

  ocx = c->x;
  ocy = c->y;
  if (XGrabPointer(wm->d, wm->r, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                   None, False /* move_cursor */, CurrentTime) != GrabSuccess)
    return;

  // grab all events while the mouse is held down
  do {
    XMaskEvent(wm->d, MOUSEMASK | ExposureMask | SubstructureRedirectMask, &e);
    switch (e.type) {
    case ConfigureRequest:
    case Expose:
    case MapRequest:
      events[e.type](&e);
      break;

    case MotionNotify:
      msg("Handling motion notify event");
      if (e.xbutton.state == (cfg.move_mask | Button1Mask) ||
          e.xbutton.state == Button1Mask) {
        nx = ocx + (e.xmotion.x - x);
        ny = ocy + (e.xmotion.y - y);
        client_move(c, nx, ny);
      } else if (e.xbutton.state == (cfg.resize_mask | Button1Mask)) {
        nw = e.xmotion.x - x;
        nh = e.xmotion.y - y;
        client_resize(c, ocw + nw, och + nh);
      }

      break;
    }
  } while (e.type != ButtonRelease);
  XUngrabPointer(wm->d, CurrentTime);
}

void setup() {
  unsigned int i, j, modifiers[] = {0, LockMask, 0, 0 | LockMask};

  wm->wscnt = wm->curr = 0;
  wm->s = DefaultScreen(wm->d);
  wm->r = RootWindow(wm->d, wm->s);

  move_cursor = XCreateFontCursor(wm->d, XC_crosshair);
  normal_cursor = XCreateFontCursor(wm->d, XC_left_ptr);
  XDefineCursor(wm->d, wm->r, normal_cursor);

  XSelectInput(wm->d, wm->r,
               SubstructureRedirectMask | SubstructureNotifyMask |
                   ButtonPressMask | Button1Mask);

  // instantiate at least one workspace
  ws_add();

  // provide a default cursor
  /* xerrorxlib = XSetErrorHandler(xerror); */
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
  /* XWindowAttributes attr; */
  XEvent ev;

  if ((wm = calloc(0, sizeof(wm))) == NULL)
    die("Could not allocate memory for the wm struct");

  // Exit if display doesn't instantiate
  if (!(wm->d = XOpenDisplay(0x0)))
    die("Could not open the Xorg display");

  if (find_autostart())
    run_autostart();

  setup();

  XSync(wm->d, False);
  while (!XNextEvent(wm->d, &ev)) {
    msg("Received event of type: %d", ev.type);
    if (events[ev.type]) {
      events[ev.type](&ev);
    }
  }

  cleanup();
}

/* XButtonEvent start; */
/* start.subwindow = None; */
/* if (ev.type == KeyPress && ev.xkey.subwindow != None) { */

/*   // Close window with mod+q */
/*   if (ev.xkey.keycode == XKeysymToKeycode(wm->d, XStringToKeysym("q"))) {
 */
/*     XDestroyWindow(wm->d, foc); */
/*   } */

/*   // Lower windows with mod+a */
/*   else if (ev.xkey.keycode == */
/*            XKeysymToKeycode(wm->d, XStringToKeysym("a"))) { */
/*     XLowerWindow(wm->d, foc); */
/*   } */

/*   // Raise windows with mod+s */
/*   else if (ev.xkey.keycode == */
/*            XKeysymToKeycode(wm->d, XStringToKeysym("s"))) { */
/*     XRaiseWindow(wm->d, foc); */
/*   } */
/* } */

/* if (ev.type == KeyPress) { */
/*   // Open simple terminal with mod+return */
/*   if (ev.xkey.keycode == */
/*       XKeysymToKeycode(wm->d, XStringToKeysym("Return"))) { */
/*     system("alacritty &"); */
/*   } */

/*   // Open dmenu with mod+d */
/*   if (ev.xkey.keycode == XKeysymToKeycode(wm->d, XStringToKeysym("d"))) {
 */
/*     system("dmenu_run"); */
/*   } */

/*   // Close aphelia with mod+backspace */
/*   else if (ev.xkey.keycode == */
/*            XKeysymToKeycode(wm->d, XStringToKeysym("BackSpace"))) { */
/*     XCloseDisplay(wm->d); */
/*   } */
/* } */

/* } */

/* if (ev.xbutton.subwindow != None) { */

/*   XGetWindowAttributes(wm->d, ev.xbutton.subwindow, &attr); */
/*   XSetInputFocus(wm->d, ev.xbutton.subwindow, RevertToParent, CurrentTime);
 */

/*   start = ev.xbutton; */
/* } else if (ev.type == MotionNotify && start.subwindow != None) { */

/*   int xdiff = ev.xbutton.x_root - start.x_root; */
/*   int ydiff = ev.xbutton.y_root - start.y_root; */

/*   XMoveResizeWindow(wm->d, start.subwindow, */
/*                     attr.x + (start.button == 1 ? xdiff : 0), */
/*                     attr.y + (start.button == 1 ? ydiff : 0), */

/*                     MAX(100, attr.width + (start.button == 3 ? xdiff : 0)),
 */

/*                     MAX(50, attr.height + (start.button == 3 ? ydiff : *0)));
 */
/* } else if (ev.type == ButtonRelease) { */

/*   start.subwindow = None; */
/* } */
