#ifndef DATA_H
#define DATA_H

typedef struct list list_t;
typedef struct stack stack_t;

struct list {
  void *value;
  struct list *next;
};

struct stack {
  void *value;
  struct stack *prev;
};

void list_append(list_t **l, void *ele);
void list_remove(list_t **l, void *ele);
void list_free(list_t *l, void (*free)(void *));
int list_size(list_t *l);

void stack_push(stack_t **s, void *ele);
void *stack_pop(stack_t **s);
void stack_remove(stack_t **s, void *ele);
void stack_free(stack_t *s);

#endif // DATA_H
