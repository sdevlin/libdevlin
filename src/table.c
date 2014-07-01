#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"

typedef struct binding binding;

struct binding {
  void *key;
  void *value;
};

struct table {
  table_cmp cmp;
  table_hash hash;
  size_t length;
  size_t slotslen;
  binding slots[0];
};

static int primes[] = {
  31, 31, 31, 31, 31, 31, 67, 127, 257, 509,
  1021, 2053, 4093, 8191, 16381, 32771, 65521
};

static size_t infer_slotslen(size_t hint) {
  size_t i;

  if (hint > 0) {
    i = ceil(log2(hint));
  } else {
    i = 0;
  }

  return primes[i];
}

table *table_new(size_t hint, table_cmp cmp, table_hash hash) {
  table *t;
  size_t slotslen;

  assert(cmp != NULL);
  assert(hash != NULL);

  slotslen = infer_slotslen(hint);

  t = malloc((sizeof *t) + (slotslen * sizeof (binding)));
  t->cmp = cmp;
  t->hash = hash;
  t->length = 0;
  t->slotslen = slotslen;
  memset(t->slots, 0, slotslen * sizeof (binding));
  return t;
}

void table_free(table *t) {
  assert(t != NULL);

  free(t);
}

static size_t table_hash(table *t, void *key) {
  assert(t != NULL);
  assert(key != NULL);

  return t->hash(key) % t->slotslen;
}

void *table_get(table *t, void *key) {
  size_t h, i;
  binding *b;

  assert(t != NULL);
  assert(key != NULL);

  h = table_hash(t, key);
  for (i = 0; i < t->slotslen; i += 1) {
    b = t->slots[(h + i) % t->slotslen];
    if (b->key == NULL) {
      return NULL;
    } else if (table_hash(t, b->key) != h) {
      return NULL;
    } else if (!t->cmp(key, b->key)) {
      return b->value;
    }
  }

  return NULL;
}

void *table_put(table *t, void *key, void *value) {
  size_t h, i;

  assert(t != NULL);
  assert(key != NULL);

  h = table_hash(t, key);
  for (i = 0;
}

void **table_to_array(table *t) {
  assert(t != NULL);

  return NULL;
}
