#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>

#include "kiwi.h"

static void cleanup();
static void setup();

static workspace *ws_curr();
static workspace *ws_add();
static void ws_sel(int i);

static void client_add(client *c);
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

char cfgp[MAXLEN]; // path to config file
static state *wm;  // wm global state

static int clients_len = 0; // the length of the clients array
static client **clients; // list of available clients (wrapper around windows)
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

  // add it to the array of clients
  clients[clients_len - 1] = c;

  // focus it on the current workspace
  client_focus(c);
}

static client *client_from_window(Window w) {
  for (int i = 0; i < clients_len; i++)
    if (clients[i] && clients[i]->w == w)
      return clients[i];

  return NULL;
}

static void client_focus(client *c) {
  workspace *ws;

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

  c->x = x;
  c->y = y;
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
  int i, id;
  workspace *ws;

  for (i = 0; i < clients_len; i++)
    if (clients[i] == c) {
      id = i;
      break;
    }

  // replace clients coming afterwards
  for (; i < clients_len; i++)
    clients[i] = clients[i - 1];

  // remove the focused reference from any workspace (if avaiable)
  for (i = 0; i < wm->wscnt; i++) {
    ws = wm->ws[i];

    if (ws->foc == c)
      // TODO: refocus !!!
      ws->foc = NULL;
  }

  msg("Removed client %i(%d) from memory", id, c->w);
  clients_len--;
  free(c);
}

static workspace *ws_curr() { return wm->ws[wm->curr]; }

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
  } else if ((wm->ws = realloc(wm->ws, sizeof(workspace *) * wm->wscnt)) ==
             NULL) {
    die("Cannot increase array of workspaces");
  }

  wm->ws[wm->wscnt - 1] = ws;
  return ws;
}

static void ws_sel(int i) { wm->curr = i; }

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
      warn("Invalid kiwic message (command)");
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
  c->ws = ws_curr()->i;
  c->x = wa->x;
  c->y = wa->y;
  c->width = wa->width;
  c->height = wa->height;
  c->border = wa->border_width;

  client_add(c);
  client_center(c);

  // map the window(show)
  XMapWindow(wm->d, c->w);

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

  client_focus(c);
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

static void setup() {
  wm->wscnt = wm->curr = 0;
  wm->s = DefaultScreen(wm->d);
  wm->r = RootWindow(wm->d, wm->s);
  int s = DefaultScreen(wm->d);
  wm->width = DisplayWidth(wm->d, s);
  wm->height = DisplayHeight(wm->d, s);

  // gather atoms
  net_kiwi[KiwiClientEvent] = XInternAtom(wm->d, KIWI_CLIENT_EVENT, False);

  wm_atom[WMDeleteWindow] = XInternAtom(wm->d, "WM_DELETE_WINDOW", False);
  wm_atom[WMTakeFocus] = XInternAtom(wm->d, "WM_TAKE_FOCUS", False);
  wm_atom[WMProtocols] = XInternAtom(wm->d, "WM_PROTOCOLS", False);

  move_cursor = XCreateFontCursor(wm->d, XC_crosshair);
  normal_cursor = XCreateFontCursor(wm->d, XC_left_ptr);
  XDefineCursor(wm->d, wm->r, normal_cursor);

  XSelectInput(wm->d, wm->r,
               SubstructureRedirectMask | SubstructureNotifyMask |
                   ButtonPressMask | Button1Mask);

  // instantiate at least one workspace
  ws_add();

  // provide a default cursor
  xerrorxlib = XSetErrorHandler(xerror);
}

int main(void) {
  /* XWindowAttributes attr; */
  XEvent ev;

  if ((wm = calloc(0, sizeof(wm))) == NULL)
    die("Could not allocate memory for the wm struct");

  // Exit if display doesn't instantiate
  if (!(wm->d = XOpenDisplay(NULL)))
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
