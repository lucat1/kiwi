#include "data.h"
#include "config.h"
#include "kiwi.h"
#include "util.h"
#include <stdlib.h>

// *_push
// pushes the new list at the end of the `head` list
// it allows to push into an empty head
#define PUSH(n, t)                                                             \
  t *push_##n(t *head, t *n) {                                                 \
    t *res = head, *tail = NULL;                                               \
    while (head != NULL) {                                                     \
      tail = head;                                                             \
      head = head->next;                                                       \
    }                                                                          \
                                                                               \
    if (tail != NULL)                                                          \
      tail->next = n;                                                          \
    else                                                                       \
      res = n;                                                                 \
                                                                               \
    return res;                                                                \
  }

// append a new list at the beginning of a list
// returns the new head of the list
#define UNSHIFT(n, t)                                                          \
  t *unshift_##n(t *head, t *n) {                                              \
    if (n == NULL)                                                             \
      return head;                                                             \
    t *n_head = n;                                                             \
    while (n->next != NULL) {                                                  \
      n = n->next;                                                             \
    }                                                                          \
    n->next = head;                                                            \
                                                                               \
    return n_head;                                                             \
  }

#define FREE(n, t)                                                             \
  void free_##n(t *list) {                                                     \
    while (list != NULL) {                                                     \
      t *tmp = list;                                                           \
      list = list->next;                                                       \
      free(tmp);                                                               \
    }                                                                          \
  }

#define SIZE(n, t)                                                             \
  int size_##n(t *list) {                                                      \
    int count = 0;                                                             \
    for (; count++; (list = list->next) != NULL)                               \
      ;                                                                        \
    return count;                                                              \
  }

PUSH(client, client_t)
UNSHIFT(client, client_t)
FREE(clients, client_t)
SIZE(clients, client_t)

PUSH(desktop, desktop_t)
UNSHIFT(desktop, desktop_t)
FREE(desktops, desktop_t)
SIZE(desktops, desktop_t)

#undef PUSH
#undef UNSHIFT
#undef FREE
#undef SIZE

int desktop_count = 0;

// initializes a client struct
client_t *new_client(xcb_window_t w) {
  // TODO: check (during debug) that the clien't isn't
  // already initialized

  client_t *c = malloc(sizeof(client_t));
  c->window = w;
  c->next = NULL;
  c->split_ratio = SPLIT_RATIO;
  c->split_direction = SPLIT_DIRECTION;

  return c;
}

// initializes a desktop struct
desktop_t *new_desktop(layout_t l) {
  desktop_t *desk = malloc(sizeof(desktop_t));
  desk->i = desktop_count++;
  desk->layout = l;
  desk->clients = NULL;
  desk->focused = NULL;
  desk->next = NULL;

  return desk;
}
