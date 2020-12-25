#ifndef LIST_H
#define LIST_H

struct list {
  void *value;
  struct list *next;
};
typedef struct list list_t;

void list_append(list_t **l, void *ele);
void list_remove(list_t **l, void *ele);
void list_free(list_t *l, void (*free)(void *));
int list_size(list_t *l);

#endif // LIST_H
