#ifndef DEVLIN_LIST_H
#define DEVLIN_LIST_H

#include <stddef.h>

typedef struct list list;

struct list {
  list *rest;
  void *item;
};

extern list list_nil;
#define LIST_NIL (&list_nil)

typedef void (*list_proc)(void **ip, void *data);
typedef int (*list_pred)(void *item, void *data);

extern void list_free(list *l);
extern list *list_items(void *item, ...);
extern list *list_copy(list *l);
extern size_t list_length(list *l);
extern int list_nil_p(list *l);
extern list *list_push(list *l, void *item);
extern list *list_pop(list *l, void **ip);
extern list *list_append(list *l, list *other);
extern list *list_reverse(list *l);
extern void *list_nth(list *l, size_t n);
extern void *list_first(list *l);
extern void *list_last(list *l);
extern void list_each(list *l, list_proc proc, void *data);
extern void *list_find(list *l, list_pred pred, void *data);
extern void **list_to_array(list *l, void *end);

#endif
