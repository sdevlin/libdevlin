#ifndef DEVLIN_ARRAY_H
#define DEVLIN_ARRAY_H

#include <stddef.h>

typedef struct array array;

extern array *array_new(size_t length, size_t itemsize);
extern void array_free(array *a);
extern array *array_copy(array *a);
extern void array_resize(array *a, size_t length);
extern size_t array_length(array *a);
extern size_t array_itemsize(array *a);
extern void *array_get(array *a, size_t i);
extern void array_put(array *a, size_t i, void *item, void **oldp);

#endif
