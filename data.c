#include "data.h"
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

PUSH(client, client_t)
UNSHIFT(client, client_t)
FREE(clients, client_t)

PUSH(desktop, desktop_t)
UNSHIFT(desktop, desktop_t)
FREE(desktops, desktop_t)

int desktop_count = 0;

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
