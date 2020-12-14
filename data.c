#include "data.h"
#include <stdlib.h>

// *_push
// pushes the new list at the end of the `head` list
// it allows to push into an empty head
#define PUSH(n, t)                                                             \
  t *push_##n(t *head, t *new) {                                               \
    t *res = head, *tail = NULL;                                               \
    while (head != NULL) {                                                     \
      tail = head;                                                             \
      head = head->next;                                                       \
    }                                                                          \
                                                                               \
    if (tail != NULL)                                                          \
      tail->next = new;                                                        \
    else                                                                       \
      res = new;                                                               \
                                                                               \
    return res;                                                                \
  }

// append a new list at the beginning of a list
// returns the new head of the list
#define UNSHIFT(n, t)                                                          \
  t *unshift_##n(t *head, t *new) {                                            \
    if (new == NULL)                                                           \
      return head;                                                             \
    t *new_head = new;                                                         \
    while (new->next != NULL) {                                                \
      new = new->next;                                                         \
    }                                                                          \
    new->next = head;                                                          \
                                                                               \
    return new_head;                                                           \
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
FREE(client, client_t)

PUSH(desktop, desktop_t)
UNSHIFT(desktop, desktop_t)
FREE(desktop, desktop_t)
