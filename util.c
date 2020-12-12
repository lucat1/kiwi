#include "util.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <xcb/xcb.h>

#ifdef DEBUG
void _print(const char *t, const char *fn, const char *f, const int l,
            const char *fmt, ...) {
#else
void _print(const char *t, const char *fmt, ...) {
#endif // DEBUG
  va_list args;

  va_start(args, fmt);

#ifdef DEBUG
  printf("[%s] (%s in %s:%d) ", t, fn, f, l);
#else
  printf("[%s] ", t);
#endif // DEBUG
  vprintf(fmt, args);
  printf("\n");

  va_end(args);
}

// borrowed and adjusted from bspwm.
// thank you baskerville
bool xcb_has_error(xcb_connection_t *dpy) {
  int xerr;
  if ((xerr = xcb_connection_has_error(dpy)) == 0) {
    return false;
  }

  char msg[256];
  switch (xerr) {
  case XCB_CONN_ERROR:
    strcpy(msg, "socket, pipe or stream error.");
    break;
  case XCB_CONN_CLOSED_EXT_NOTSUPPORTED:
    strcpy(msg, "unsupported extension.");
    break;
  case XCB_CONN_CLOSED_MEM_INSUFFICIENT:
    strcpy(msg, "not enough memory.");
    break;
  case XCB_CONN_CLOSED_REQ_LEN_EXCEED:
    strcpy(msg, "request length exceeded.");
    break;
  case XCB_CONN_CLOSED_PARSE_ERR:
    strcpy(msg, "can't parse display string.");
    break;
  case XCB_CONN_CLOSED_INVALID_SCREEN:
    strcpy(msg, "invalid screen.");
    break;
  case XCB_CONN_CLOSED_FDPASSING_FAILED:
    strcpy(msg, "failed to pass FD.");
    break;
  default:
    strcpy(msg, "unknown error.");
    break;
  }

  fail("The server closed the connection: %s", msg);
  return true;
}
