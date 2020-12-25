#include "data.h"
#include "config.h"
#include "kiwi.h"
#include "util.h"
#include <stdlib.h>
#include <xcb/xcb.h>

// *_push
// pushes the new list at the end of the `head` list
// it allows to push into an empty head
#define PUSH(n, t)                                                             \
  t *push_##n(t *iter, t *n) {                                                 \
    if (iter == NULL)                                                          \
      return n;                                                                \
                                                                               \
    t *head = iter;                                                            \
    while (iter->next != NULL) {                                               \
      iter = iter->next;                                                       \
    }                                                                          \
    iter->next = n;                                                            \
    return head;                                                               \
  }

// append a new list at the beginning of a list
// returns the new head of the list
#define UNSHIFT(n, t)                                                          \
  t *unshift_##n(t *head, t *n) {                                              \
    if (n == NULL)                                                             \
      return head;                                                             \
                                                                               \
    t *n_head = n;                                                             \
    while (n->next != NULL) {                                                  \
      n = n->next;                                                             \
    }                                                                          \
    n->next = head;                                                            \
                                                                               \
    return n_head;                                                             \
  }

// removes the given node from the list
// returning the updated list (as the head may change)
#define REMOVE(n, t)                                                           \
  t *remove_##n(t *iter, t *n) {                                               \
    t *head = iter, *prev = NULL;                                              \
    while (iter != NULL) {                                                     \
      if (iter == n) {                                                         \
        t *tmp = iter;                                                         \
        if (prev == NULL) {                                                    \
          head = iter->next;                                                   \
        } else {                                                               \
          prev->next = iter->next;                                             \
        }                                                                      \
        iter = iter->next;                                                     \
        free(tmp);                                                             \
      } else {                                                                 \
        prev = iter;                                                           \
        iter = iter->next;                                                     \
      }                                                                        \
    }                                                                          \
    return head;                                                               \
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
    for (; (list = list->next) != NULL; count++)                               \
      ;                                                                        \
    return count;                                                              \
  }

PUSH(client, client_t)
UNSHIFT(client, client_t)
REMOVE(client, client_t)
FREE(clients, client_t)
SIZE(clients, client_t)

PUSH(desktop, desktop_t)
UNSHIFT(desktop, desktop_t)
REMOVE(desktop, desktop_t)
FREE(desktops, desktop_t)
SIZE(desktops, desktop_t)

#undef PUSH
#undef UNSHIFT
#undef REMOVE
#undef FREE
#undef SIZE

int desktop_count = 0;

// initializes a client struct
client_t *new_client(xcb_window_t w) {
#ifdef DEBUG
  if (get_client(w) != NULL)
    fail("attempted to initialize new client with an existing window %d", w);
#endif

  client_t *c = malloc(sizeof(client_t));
  c->window = w;
  c->next = NULL;
  c->split_ratio = SPLIT_RATIO;
  c->split_direction = SPLIT_DIRECTION;

  return c;
}

client_t *get_client(xcb_window_t w) {
  desktop_t *diter = desktops;
  while (diter != NULL) {
    client_t *citer = diter->clients;
    while (citer != NULL) {
      if (citer->window == w)
        return citer;

      citer = citer->next;
    }

    diter = diter->next;
  }

  return NULL;
}

// initializes a desktop struct
desktop_t *new_desktop(layout_t l) {
  desktop_t *desk = malloc(sizeof(desktop_t));
  desk->i = desktop_count++;
  desk->layout = l;
  desk->clients = NULL;
  desk->focused = NULL;
  desk->focus_stack = NULL;
  desk->next = NULL;

  return desk;
}
