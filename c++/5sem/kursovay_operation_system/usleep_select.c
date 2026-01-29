#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <sys/select.h>
#include <unistd.h>

/*
 * usleep_select(usec)
 * Возвращает 0, если "сон" отработал полностью.
 * Возвращает -1, если был прерван сигналом (errno будет EINTR).
 */
int usleep_select(useconds_t usec) {
  struct timeval tv;
  tv.tv_sec = (time_t)(usec / 1000000);
  tv.tv_usec = (suseconds_t)(usec % 1000000);

  int rc = select(0, NULL, NULL, NULL, &tv);
  if (rc == 0)
    return 0;
  if (rc == -1)
    return -1;

  errno = EIO;
  return -1;
}

#ifdef DEMO
#include <stdio.h>
int main(void) {
  puts("Sleeping for 500000 usec...");
  if (usleep_select(500000) == -1)
    perror("usleep_select");
  else
    puts("Done");
  return 0;
}
#endif
