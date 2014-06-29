#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <typedef.h>

struct array {
  size_t length;
  size_t itemsize;
  byte data[0];
};

array *array_new(size_t length, size_t itemsize) {
  array *a;
  size_t datasize;

  datasize = length * itemsize; /* TODO check overflow */
  a = malloc((sizeof length) + (sizeof itemsize) + datasize);
  a->length = length;
  a->itemsize = itemsize;
  memset(a->data, 0, datasize);
  return a;
}
