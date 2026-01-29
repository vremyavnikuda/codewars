#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef BOOL
#define BOOL int
#define TRUE 1
#define FALSE 0
#endif

static void fatal_error(int err, const char *msg) {
  if (err == 0)
    err = errno;
  fprintf(stderr, "%s: %s\n", msg, strerror(err));
  exit(EXIT_FAILURE);
}

static ssize_t read_full(int fd, void *buf, size_t n) {
  size_t off = 0;
  while (off < n) {
    ssize_t r = read(fd, (char *)buf + off, n - off);
    if (r == 0)
      return 0;
    if (r < 0) {
      if (errno == EINTR)
        continue;
      return -1;
    }
    off += (size_t)r;
  }
  return (ssize_t)off;
}

static int make_fifo_path(const char *qname, char *out, size_t outsz) {
  if (!qname || qname[0] == '\0')
    return -1;

  const char *p = qname;
  if (p[0] == '/')
    p++;

  char tmp[128];
  size_t j = 0;
  for (; *p != '\0' && j + 1 < sizeof(tmp); ++p) {
    char c = *p;
    if (c == '/')
      c = '_';
    tmp[j++] = c;
  }
  tmp[j] = '\0';

  if (j == 0)
    return -1;

  int n = snprintf(out, outsz, "/tmp/mqsim_%s.fifo", tmp);
  if (n < 0 || (size_t)n >= outsz)
    return -1;
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s /queue_name\n", argv[0]);
    return EXIT_FAILURE;
  }

  char fifopath[256];
  if (make_fifo_path(argv[1], fifopath, sizeof(fifopath)) != 0) {
    fprintf(stderr, "Invalid queue name\n");
    return EXIT_FAILURE;
  }

  if (mkfifo(fifopath, 0660) == -1 && errno != EEXIST)
    fatal_error(errno, "mkfifo");

  int fd = open(fifopath, O_RDWR);
  if (fd == -1)
    fatal_error(errno, "open(fifo) read");

  BOOL done = FALSE;
  while (!done) {
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);
    FD_SET(fd, &rfds);

    int maxfd = (STDIN_FILENO > fd) ? STDIN_FILENO : fd;

    int rc = select(maxfd + 1, &rfds, NULL, NULL, NULL);
    if (rc < 0) {
      if (errno == EINTR)
        continue;
      fatal_error(errno, "select");
    }

    if (FD_ISSET(STDIN_FILENO, &rfds)) {
      char ch = 0;
      ssize_t r = read(STDIN_FILENO, &ch, 1);
      if (r > 0 && ch == 'q')
        done = TRUE;
    }

    if (FD_ISSET(fd, &rfds)) {
      uint32_t len32 = 0, prio32 = 0;

      ssize_t r1 = read_full(fd, &len32, sizeof(len32));
      if (r1 == 0)
        continue;
      if (r1 < 0)
        fatal_error(errno, "read(fifo) len");

      if (read_full(fd, &prio32, sizeof(prio32)) <= 0)
        fatal_error(errno, "read(fifo) prio");

      size_t payload_len = (size_t)len32;
      if (payload_len > 65536) {
        fprintf(stderr, "Message too large: %u\n", len32);
        continue;
      }

      char *payload = calloc(1, payload_len + 1);
      if (!payload)
        fatal_error(errno, "calloc payload");

      if (read_full(fd, payload, payload_len) <= 0)
        fatal_error(errno, "read(fifo) payload");

      printf("Received (%u bytes, prio=%u): %s\n", len32, prio32, payload);
      fflush(stdout);
      free(payload);
    }
  }

  close(fd);
  unlink(fifopath);
  return 0;
}
