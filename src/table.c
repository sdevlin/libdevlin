#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

#include "table.h"

typedef struct {
  void *key;
  void *value;
} binding;

struct table {
  table_cmp cmp;
  table_hash hash;
  size_t capacity;
  size_t length;
  binding **buckets;
};

static int primes[] = {
  509, 509, 1021, 2053, 4093, 8191, 16381, 32771, 65521, INT_MAX
};

table *table_new(size_t hint, table_cmp cmp, table_hash hash) {
  table *t;

  assert(cmp != NULL);
  assert(hash != NULL);

  t = malloc(sizeof *t);
  t->cmp = cmp;
  t->hash = hash;
  return t;
}

void table_free(table *t) {
  assert(t != NULL);

  free(t);
}

void **table_to_array(table *t) {
  assert(t != NULL);

  return NULL;
}
