#ifndef STACK_H
#define STACK_H

typedef struct stack stack_t;

struct stack {
  void *value;
  struct stack *prev;
};

void stack_push(stack_t **s, void *ele);
void *stack_pop(stack_t **s);
void stack_remove(stack_t **s, void *ele);
void stack_free(stack_t *s);

#endif // STACK_H
