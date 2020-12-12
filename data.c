#include "data.h"

// pushes the new list at the end of the `head` list
// it allows to push into an empty head
//
// returns the old head or the newly initialized head if the
// previous was NULL
client_t *push(client_t *head, client_t *new) {
  client_t *res = head, *tail = NULL;
  while (head != NULL) {
    tail = head;
    head = head->next;
  }

  if (tail != NULL)
    tail->next = new;
  else
    res = new;

  return res;
}

// append a new list at the beginning of a list
// returns the new head of the list
//
// NOTE: assumes new is not null
client_t *unshift(client_t *head, client_t *new) {
  client_t *new_head = new;
  while (new->next != NULL) {
    new = new->next;
  }
  new->next = head;

  return new_head;
}
