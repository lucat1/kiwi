#ifndef STACK_H
#define STACK_H

struct stack {
  void *value;
  struct stack *prev;
};
typedef struct stack stack_t;

void stack_push(stack_t **s, void *ele);
void *stack_pop(stack_t **s);
// remove all occourences of a certain element
void stack_clean(stack_t **s, void *ele);

#endif // STACK_H
