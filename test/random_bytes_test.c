#include <stdlib.h>

#include <unistd.h>

#include <random.h>
#include <typedef.h>

int main(void) {
  u8 buffer[1 << 21];

  random_bytes(buffer, sizeof buffer);

  return 0;
}
