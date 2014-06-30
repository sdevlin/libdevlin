#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <typedef.h>

struct array {
  size_t length;
  size_t itemsize;
  byte *data;
};

static size_t array_datasize(array *a) {
  assert(a != NULL);

  return a->length * a->itemsize;
}

static array *array_alloc(size_t length, size_t itemsize) {
  array *a;

  assert(length > 0);
  assert(itemsize > 0);

  a = malloc(sizeof *a);
  a->length = length;
  a->itemsize = itemsize;
  a->data = malloc(array_datasize(a));
  return a;
}

array *array_new(size_t length, size_t itemsize) {
  array *a;

  assert(length > 0);
  assert(itemsize > 0);

  a = array_alloc(length, itemsize);
  memset(a->data, 0, array_datasize(a));
  return a;
}

void array_free(array *a) {
  assert(a != NULL);

  free(a->data);
  free(a);
}

array *array_copy(array *a) {
  array *copy;

  assert(a != NULL);

  copy = array_alloc(a->length, a->itemsize);
  memcpy(copy->data, a->data, array_datasize(copy));
  return copy;
}

void array_resize(array *a, size_t length) {
  size_t olddatasize, newdatasize;

  assert(a != NULL);
  assert(length > 0);

  olddatasize = array_datasize(a);
  a->length = length;
  a->data = realloc(a->data, length * a->itemsize);
  newdatasize = array_datasize(a);
  if (newdatasize > olddatasize) {
    memset(a->data + olddatasize, 0, newdatasize - olddatasize);
  }
}

size_t array_length(array *a) {
  assert(a != NULL);

  return a->length;
}

size_t array_itemsize(array *a) {
  assert(a != NULL);

  return a->itemsize;
}

#define ARR_LOC(a, i) (a->data + (a->itemsize * i))

void *array_get(array *a, size_t i) {
  assert(a != NULL);
  assert(i < a->length);

  return ARR_LOC(a, i);
}

void array_put(array *a, size_t i, void *item, void **oldp) {
  assert(a != NULL);
  assert(i < a->length);
  assert(item != NULL);

  if (oldp != NULL) {
    *oldp = array_get(a, i);
  }
  memcpy(ARR_LOC(a, i), item, a->itemsize);
}

void array_each(array *a, array_proc proc, void *data) {
  void *item;
  size_t i;

  assert(a != NULL);
  assert(proc != NULL);

  for (i = 0; i < a->length; i += 1) {
    item = array_get(a, i);
    proc(&item, data);
  }
}

void *array_find(array *a, array_pred pred, void *data) {
  void *item;
  size_t i;

  assert(a != NULL);
  assert(pred != NULL);

  for (i = 0; i < a->length; i += 1) {
    item = array_get(a, i);
    if (pred(item, data)) {
      return item;
    }
  }

  return NULL;
}
