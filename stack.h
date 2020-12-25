#ifndef STACK_H
#define STACK_H

struct stack {
  void *value;
  struct stack *prev;
};
typedef struct stack stack_t;

void stack_push(stack_t **s, void *ele);
void *stack_pop(stack_t **s);
void stack_remove(stack_t **s, void *ele);
void stack_free(stack_t *s);

#endif // STACK_H
