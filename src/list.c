#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#include "list.h"

list list_nil;

void list_free(list *l) {
  list *prev;

  assert(l != NULL);

  while (!list_nil_p(l)) {
    prev = l;
    l = l->rest;
    free(prev);
  }
}

list *list_items(void *item, ...) {
  list *l;
  va_list ap;

  l = LIST_NIL;

  for (va_start(ap, item); item != LIST_NIL; item = va_arg(ap, void *)) {
    l = list_push(l, item);
  }
  va_end(ap);

  return list_reverse(l);
}

list *list_copy(list *l) {
  list *copy;

  assert(l != NULL);

  copy = LIST_NIL;

  for (; !list_nil_p(l); l = l->rest) {
    copy = list_push(copy, l->item);
  }

  return list_reverse(copy);
}

size_t list_length(list *l) {
  size_t length;

  assert(l != NULL);

  length = 0;
  while (!list_nil_p(l)) {
    length += 1;
    l = l->rest;
  }

  return length;
}

int list_nil_p(list *l) {
  assert(l != NULL);

  return l == LIST_NIL;
}

list *list_push(list *l, void *item) {
  list *new;

  assert(l != NULL);

  new = malloc(sizeof *new);
  new->item = item;
  new->rest = l;
  return new;
}

list *list_pop(list *l, void **ip) {
  list *old;

  assert(l != NULL);

  old = l;
  if (ip != NULL) {
    *ip = l->item;
  }
  l = l->rest;
  free(old);
  return l;
}

list *list_append(list *l, list *other) {
  list *head;

  assert(l != NULL);
  assert(other != NULL);

  head = l;
  while (list_nil_p(l->rest)) {
    l = l->rest;
  }
  l->rest = other;

  return l;
}

list *list_reverse(list *l) {
  list *prev;
  list *next;

  assert(l != NULL);

  prev = LIST_NIL;
  while (!list_nil_p(l)) {
    next = l->rest;
    l->rest = prev;
    prev = l;
    l = next;
  }

  return prev;
}

void *list_nth(list *l, size_t n) {
  assert(l != NULL);

  for (; !list_nil_p(l); n -= 1, l = l->rest) {
    if (n == 0) {
      return l->item;
    }
  }

  return NULL;
}

void *list_first(list *l) {
  assert(l != NULL);

  return list_nil_p(l) ? NULL : l->item;
}

void *list_last(list *l) {
  assert(l != NULL);

  if (list_nil_p(l)) {
    return NULL;
  }

  while (!list_nil_p(l->rest)) {
    l = l->rest;
  }

  return l->item;
}

void list_each(list *l, list_proc proc, void *data) {
  assert(l != NULL);
  assert(proc != NULL);

  for (; !list_nil_p(l); l = l->rest) {
    proc(&l->item, data);
  }
}

void *list_find(list *l, list_pred pred, void *data) {
  void *item;

  assert(l != NULL);
  assert(pred != NULL);

  for (; !list_nil_p(l); l = l->rest) {
    item = l->item;
    if (pred(item, data)) {
      return item;
    }
  }

  return NULL;
}

void **list_to_array(list *l, void *end) {
  void **array;
  void **p;

  assert(l != NULL);

  array = malloc((list_length(l) + 1) * (sizeof (void *)));
  for (p = array; !list_nil_p(l); p += 1, l = l->rest) {
    *p = l->item;
  }
  *p = end;

  return array;
}
