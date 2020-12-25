#include "list.h"
#include <stdlib.h>

void list_append(list_t **l, void *ele) {
  list_t *n = malloc(sizeof(list_t));
  n->next = NULL;
  n->value = ele;
  if (*l == NULL)
    *l = n;
  else {
    list_t *iter = *l;
    while (iter->next != NULL)
      iter = iter->next;
    iter->next = n;
  }
}

void list_remove(list_t **l, void *ele) {
  list_t *head = *l, *iter = *l, *prev = NULL;
  while (iter != NULL) {
    if (iter->value == ele) {
      list_t *tmp = iter;
      if (prev == NULL)
        head = iter->next;
      else
        prev->next = iter->next;

      iter = iter->next;
      free(tmp);
    } else {
      prev = iter;
      iter = iter->next;
    }
  }

  *l = head;
}

int list_size(list_t *iter) {
  int count = 0;
  while (iter != NULL) {
    count++;
    iter = iter->next;
  }

  return count;
}

void list_free(list_t *iter, void (*custom_free)(void *)) {
  while (iter != NULL) {
    list_t *tmp = iter;
    iter = iter->next;

    // call custom free function if required
    if (custom_free != NULL)
      custom_free(tmp->value);
    free(tmp);
  }
}
