#ifndef DEVLIN_TABLE_H
#define DEVLIN_TABLE_H

#include <stddef.h>

#include "typedef.h"

typedef struct table table;
typedef int (*table_cmp)(void *k1, void *k2);
typedef uint (*table_hash)(void *key);
typedef void (*table_proc)(void *key, void **vp, void *data);
typedef int (*table_pred)(void *key, void *value, void *data);

extern table *table_new(size_t hint, table_cmp cmp, table_hash hash);
extern void table_free(table *t);
extern void *table_get(table *t, void *key);
extern void *table_put(table *t, void *key, void *value);
extern void *table_remove(table *t, void *key);

#endif
