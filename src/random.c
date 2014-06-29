#include <stddef.h>

#include <fcntl.h>
#include <unistd.h>

#include "typedef.h"
#include "random.h"

/* lifted directly from djb's nacl */

static int fd = -1;

#define MAX_READ (1 << 20)

void random_bytes(byte *buf, size_t buflen) {
  size_t i;

  if (fd == -1) {
    for (;;) {
      fd = open("/dev/urandom", O_RDONLY);
      if (fd != -1) {
        break;
      }
      sleep(1);
    }
  }

  while (buflen > 0) {
    i = buflen < MAX_READ ? buflen : MAX_READ;

    i = read(fd, buf, i);

    if (i < 1) {
      sleep(1);
    }

    buf += i;
    buflen -= i;
  }
}
