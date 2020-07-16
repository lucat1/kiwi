#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>

#include "kiwi.h"
#include "vector.h"

static void cleanup();
static void setup();

static workspace *ws_curr();
static workspace *ws_add();
static void ws_delete(size_t ws);
static void ws_focus(size_t ws);
static cvector_vector_type(client *) clients_from_ws(size_t ws);

static client *client_from_window();
static void client_add(client *c);
static void client_show(client *c);
static void client_hide(client *c);
static void client_focus(client *c);
static void client_move(client *c, int x, int y);
static void client_resize(client *c, int w, int h);
static void client_close(client *c);
static void client_kill(client *c);
static void client_delete(client *c);

static void handle_map_request(XEvent *ev);
static void handle_unmap_notify(XEvent *ev);
static void handle_client_message(XEvent *ev);
static void handle_button_press(XEvent *ev);
static void handle_new_window(Window w, XWindowAttributes *wa);

static void kiwic_close(long *e);
static void kiwic_kill(long *e);
static void kiwic_workspaces(long *e);
static void kiwic_focus_workspace(long *e);

char cfgp[MAXLEN]; // path to config file
state *wm;         // wm global state

/* static int clients_len = 0; // the length of the clients array */
/* static client **clients; // list of available clients (wrapper around
 * windows) */
static config cfg = {Mod4Mask};
static Atom wm_atom[WMLast], net_kiwi[KiwiLast];

static Cursor move_cursor, normal_cursor;
static int (*xerrorxlib)(Display *, XErrorEvent *);

static void (*events[LASTEvent])(XEvent *e) = {
    [MapRequest] = handle_map_request,
    [UnmapNotify] = handle_unmap_notify,
    [ClientMessage] = handle_client_message,
    [ButtonPress] = handle_button_press,
};

static void (*kiwic_events[KiwicLast])(long *) = {
    [KiwicClose] = kiwic_close,
    [KiwicKill] = kiwic_kill,

    [KiwicWorkspaces] = kiwic_workspaces,
    [KiwicFocusWorkspace] = kiwic_focus_workspace,
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

  die("fatal error: request code=%d, error code=%d", ee->request_code,
      ee->error_code);
  return xerrorxlib(d, ee); /* may call exit */
}

static void cleanup() {
  size_t i;

  if (wm == NULL)
    return;

  // free any workspace
  if (wm->ws != NULL)
    cvector_free(wm->ws);

  if (wm->cs != NULL) {
    for (i = 0; i < cvector_size(wm->cs); i++)
      free(wm->cs[i]);

    cvector_free(wm->cs);
  }

  msg("Closing the display");
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

static workspace *ws_curr() { return wm->ws[wm->focus]; }

static workspace *ws_add() {
  size_t i = cvector_size(wm->ws);
  workspace *ws;

  if ((ws = calloc(0, sizeof(workspace))) == NULL)
    die("Cannot allocate memory for a new workspace");

  ws->i = i;
  cvector_push_back(wm->ws, ws);

  msg("Added workspace %i", ws->i);
  return ws;
}

static void ws_delete(size_t ws) {
  size_t i;
  cvector_vector_type(client *) cs;

  if (cvector_size(wm->ws) < ws) {
    warn("Could not delete workspace %i, it does not exist", ws);
    return;
  }

  // first, kill any windows in the workspace
  if ((cs = clients_from_ws(ws)) != NULL) {
    for (i = 0; i < cvector_size(cs); i++)
      client_kill(cs[i]);

    // we need to free the array allocated by `clients_from_ws`
    cvector_free(cs);
  }

  // if the workspace was focused, shift focus to the previous one.
  // the previous ws will always be available as we cannot go to -1 number of ws
  if (wm->focus == ws)
    ws_focus(ws - 1);

  msg("Removed workspace %i", ws);
  // lastly remove the workspace from the vector and free some memory
  cvector_erase(wm->ws, ws);
}

static void ws_focus(size_t ws) {
  size_t i;
  cvector_vector_type(client *) cs;
  msg("Focusing workspace (from)%i->%i(to)", wm->focus, ws);

  if (ws == wm->focus)
    return;

  // hide previous windows
  if ((cs = clients_from_ws(wm->focus)) != NULL) {
    for (i = 0; i < cvector_size(cs); i++)
      client_hide(cs[i]);

    cvector_free(cs);
  }

  wm->focus = ws;
  if ((cs = clients_from_ws(wm->focus)) != NULL) {
    for (i = 0; i < cvector_size(cs); i++)
      client_show(cs[i]);

    cvector_free(cs);
  }

  // focus the old client in the workspace if any
  if (ws_curr()->foc)
    client_focus(ws_curr()->foc);
}

static cvector_vector_type(client *) clients_from_ws(size_t ws) {
  size_t i;
  cvector_vector_type(client *) cs = NULL;

  for (i = 0; i < cvector_size(wm->cs); i++) {
    if (wm->cs[i]->ws != ws)
      continue;

    cvector_push_back(cs, wm->cs[i]);
  }

  return cs;
}

static client *client_from_window(Window w) {
  size_t i;

  for (i = 0; i < cvector_size(wm->cs); i++)
    if (wm->cs[i] && wm->cs[i]->w == w)
      return wm->cs[i];

  return NULL;
}

static void client_add(client *c) {
  msg("adding client to workspace %i(%lu) [x: %i, y: %i, w: %i, h: %i]", c->ws,
      c->w, c->x, c->y, c->width, c->height);

  // add it to the array of clients
  cvector_push_back(wm->cs, c);
}

static void client_show(client *c) {
  // map the window(show)
  msg("showing window: %d", c->w);

  c->visible = True;
  client_move(c, c->x, c->y);
}

static void client_hide(client *c) {
  // unmap the window(hide)
  msg("hiding window: %d", c->w);

  c->visible = False;
  client_move(c, wm->width, wm->height);
}

static void client_focus(client *c) {
  workspace *ws;
  msg("focusing %p, w: %i", c, c->w);

  ws = ws_curr();
  ws->foc = c;

  XSetInputFocus(wm->d, c->w, RevertToPointerRoot, CurrentTime);
  XRaiseWindow(wm->d, c->w);
}

static void client_center(client *c) {
  int x, y;

  x = (wm->width - c->width) / 2;
  y = (wm->height - c->height) / 2;

  client_move(c, x, y);
}

static void client_move(client *c, int x, int y) {
  XMoveWindow(wm->d, c->w, x, y);

  // DO NOT update the coordinates in the client object
  // when we move the window during a hidden state
  if (c->visible) {
    c->x = x;
    c->y = y;
  }
}

static void client_resize(client *c, int w, int h) {
  XResizeWindow(wm->d, c->w, MAX(w, MINIMUM_DIM), MAX(h, MINIMUM_DIM));

  c->width = MAX(w, MINIMUM_DIM);
  c->height = MAX(h, MINIMUM_DIM);
}

static void client_close(client *c) {
  XEvent ev;

  ev.type = ClientMessage;
  ev.xclient.window = c->w;
  ev.xclient.message_type = wm_atom[WMProtocols];
  ev.xclient.format = 32;
  ev.xclient.data.l[0] = wm_atom[WMDeleteWindow];
  ev.xclient.data.l[1] = CurrentTime;

  XSendEvent(wm->d, c->w, False, NoEventMask, &ev);
  msg("Closing client %d", c->w);
}

static void client_kill(client *c) { XKillClient(wm->d, c->w); }

// removes the client from any leftover reference and frees the memory
static void client_delete(client *c) {
  size_t i, id;
  workspace *ws;

  for (i = 0; i < cvector_size(wm->cs); i++)
    if (wm->cs[i] == c) {
      id = i;
      break;
    }

  // remove the focused reference from any workspace (if avaiable)
  for (i = 0; i < cvector_size(wm->ws); i++) {
    ws = wm->ws[i];

    if (ws->foc == c)
      // TODO: refocus !!!
      ws->foc = NULL;
  }

  msg("Removed client %i(w: %d)", id, c->w);
  cvector_erase(wm->cs, i);
  free(c);
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

static void handle_unmap_notify(XEvent *ev) {
  XUnmapEvent *e = &ev->xunmap;
  client *c = client_from_window(e->window);

  if (c == NULL) {
    warn("Recieved UnmapNotify event for a non-managed client %d", e->window);
    return;
  }

  /* focus_best(c); */
  client_delete(c);
}

static void handle_client_message(XEvent *ev) {
  XClientMessageEvent *cme = &ev->xclient;
  long cmd, *data;

  if (cme->message_type == net_kiwi[KiwiClientEvent]) {
    if (cme->format != 32) {
      warn("Invalid message format. Ignoring");
      return;
    }

    msg("Recieved kiwic message");
    cmd = cme->data.l[0];
    data = cme->data.l;
    if (kiwic_events[cmd])
      kiwic_events[cmd](data);
    else
      warn("Invalid kiwic command (%li)", cmd);
  }

  msg("Unhandled client message: %lu", cme->message_type);
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
  c->visible = True;
  c->ws = wm->focus;
  c->x = wa->x;
  c->y = wa->y;
  c->width = wa->width;
  c->height = wa->height;
  c->border = wa->border_width;

  client_add(c);
  client_center(c);

  // map it in the display(show) and
  // focus it on the current workspace
  XMapWindow(wm->d, c->w);
  client_focus(c);

  // grab events
  XSelectInput(wm->d, c->w,
               EnterWindowMask | FocusChangeMask | PropertyChangeMask |
                   StructureNotifyMask);
  XGrabButton(wm->d, Button1, Mod4Mask, c->w, True,
              ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
              GrabModeAsync, GrabModeAsync, None, None);
  XGrabButton(wm->d, Button3, Mod4Mask, c->w, True,
              ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
              GrabModeAsync, GrabModeAsync, None, None);
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

  if (c != ws_curr()->foc)
    client_focus(c);

  // make a copy of the geometry values as they'll change during resizing/moving
  ocx = c->x;
  ocy = c->y;
  ocw = c->width;
  och = c->height;

  if (XGrabPointer(wm->d, wm->r, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                   None, move_cursor, CurrentTime) != GrabSuccess)
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
      if (e.xbutton.state == (cfg.mask | Button1Mask) ||
          e.xbutton.state == Button1Mask) {
        nx = ocx + (e.xmotion.x - x);
        ny = ocy + (e.xmotion.y - y);
        client_move(c, nx, ny);
      } else if (e.xbutton.state == (cfg.mask | Button3Mask)) {
        nw = e.xmotion.x - x;
        nh = e.xmotion.y - y;
        client_resize(c, ocw + nw, och + nh);
      }

      break;
    }
  } while (e.type != ButtonRelease);
  XUngrabPointer(wm->d, CurrentTime);
}

// TODO(for both): change focused client !!!
static void kiwic_close(long *e) {
  client *c = ws_curr()->foc;
  if (c == NULL)
    return;

  client_close(c);
}

static void kiwic_kill(long *e) {
  client *c = ws_curr()->foc;
  if (c == NULL)
    return;

  client_kill(ws_curr()->foc);
}

static void kiwic_workspaces(long *e) {
  size_t count = (size_t)e[1], len = cvector_size(wm->ws), i;
  if (count < 1)
    return;

  msg("Setting number of workspaces to %i(from)->%i(to)", len, count);

  // shrink the amount of workspaces if the number is lower
  if (count < len)
    for (i = len; i >= count; i--) {
      msg("removing %i", i);
      ws_delete(i);
    }

  if (count > len)
    for (i = len; i < count; i++)
      ws_add();

  msg("remained %i workspaces", cvector_size(wm->ws));
}

static void kiwic_focus_workspace(long *e) {
  size_t ws = (size_t)e[1];

  if (cvector_size(wm->ws) <= ws)
    return;

  ws_focus(ws);
}

static void setup() {
  wm->s = DefaultScreen(wm->d);
  wm->r = RootWindow(wm->d, wm->s);
  wm->width = DisplayWidth(wm->d, wm->s);
  wm->height = DisplayHeight(wm->d, wm->s);

  // provide a default cursor
  xerrorxlib = XSetErrorHandler(xerror);

  // gather atoms
  net_kiwi[KiwiClientEvent] = XInternAtom(wm->d, KIWI_CLIENT_EVENT, False);

  wm_atom[WMDeleteWindow] = XInternAtom(wm->d, "WM_DELETE_WINDOW", False);
  wm_atom[WMTakeFocus] = XInternAtom(wm->d, "WM_TAKE_FOCUS", False);
  wm_atom[WMProtocols] = XInternAtom(wm->d, "WM_PROTOCOLS", False);

  move_cursor = XCreateFontCursor(wm->d, XC_crosshair);
  normal_cursor = XCreateFontCursor(wm->d, XC_left_ptr);
  XDefineCursor(wm->d, wm->r, normal_cursor);
  // move the cursor to the center of the desktop
  XWarpPointer(wm->d, None, wm->r, 0, 0, 0, 0, wm->width / 2, wm->height / 2);

  XSelectInput(wm->d, wm->r,
               SubstructureRedirectMask | SubstructureNotifyMask |
                   ButtonPressMask | Button1Mask);

  // instantiate at least one workspace
  wm->focus = 0;
  ws_add();
}

int main(void) {
  XEvent ev;

  if (!(wm = calloc(1, sizeof(state))))
    die("Could not allocate memory for the wm struct");

  // initialize vectors
  wm->ws = NULL;
  wm->cs = NULL;

  // Exit if display doesn't instantiate
  if (!(wm->d = XOpenDisplay(NULL)))
    die("Could not open the Xorg display");

  setup();

  if (find_autostart())
    run_autostart();

  XSync(wm->d, False);
  while (!XNextEvent(wm->d, &ev)) {
    msg("Received event of type: %d", ev.type);
    if (events[ev.type]) {
      events[ev.type](&ev);
    }
  }

  cleanup();
}
