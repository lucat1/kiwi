#include "stack.h"
#include <stdlib.h>

// TODO: OPTIMIZE:
// don't push multiple occourcences of the same *ele
// check for existing ones and move these. lowers the memory
// and allocation buren. priority low
void stack_push(stack_t **s, void *ele) {
  stack_t *n = malloc(sizeof(stack_t));
  n->prev = *s;
  n->value = ele;
  *s = n;
}

void *stack_pop(stack_t **s) {
  stack_t *ele = *s;
  *s = ele->prev;
  return ele->value;
}

void stack_remove(stack_t **s, void *ele) {
  stack_t *head = *s, *iter = *s, *prev = NULL;
  while (iter != NULL) {
    if (iter->value == ele) {
      stack_t *tmp = iter;
      if (prev == NULL)
        head = iter->prev;
      else
        prev->prev = iter->prev;

      iter = iter->prev;
      free(tmp);
    } else {
      prev = iter;
      iter = iter->prev;
    }
  }

  *s = head;
}

void stack_free(stack_t *iter) {
  while (iter != NULL) {
    stack_t *tmp = iter;
    iter = iter->prev;
    free(tmp);
  }
}
