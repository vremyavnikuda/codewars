#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void fatal_error(int err, const char *msg) {
  if (err == 0)
    err = errno;
  fprintf(stderr, "%s: %s\n", msg, strerror(err));
  exit(EXIT_FAILURE);
}

static int write_full(int fd, const void *buf, size_t n) {
  size_t off = 0;
  while (off < n) {
    ssize_t w = write(fd, (const char *)buf + off, n - off);
    if (w < 0) {
      if (errno == EINTR)
        continue;
      return -1;
    }
    off += (size_t)w;
  }
  return 0;
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
  if (argc < 3) {
    fprintf(stderr, "Usage: %s /queue_name message [prio]\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *qname = argv[1];
  const char *msg = argv[2];
  unsigned int prio = 0;
  if (argc >= 4)
    prio = (unsigned int)strtoul(argv[3], NULL, 10);

  char fifopath[256];
  if (make_fifo_path(qname, fifopath, sizeof(fifopath)) != 0) {
    fprintf(stderr, "Invalid queue name\n");
    return EXIT_FAILURE;
  }

  if (mkfifo(fifopath, 0660) == -1 && errno != EEXIST)
    fatal_error(errno, "mkfifo");

  size_t msglen = strlen(msg);
  if (msglen > UINT32_MAX) {
    fprintf(stderr, "Message too large\n");
    return EXIT_FAILURE;
  }

  size_t buflen = sizeof(uint32_t) * 2 + msglen;
  unsigned char *buf = (unsigned char *)malloc(buflen);
  if (!buf)
    fatal_error(errno, "malloc");

  uint32_t len32 = (uint32_t)msglen;
  uint32_t prio32 = (uint32_t)prio;
  memcpy(buf, &len32, sizeof(len32));
  memcpy(buf + sizeof(len32), &prio32, sizeof(prio32));
  memcpy(buf + sizeof(uint32_t) * 2, msg, msglen);

  int fd = open(fifopath, O_WRONLY);
  if (fd == -1)
    fatal_error(errno, "open(fifo) write");

  if (write_full(fd, buf, buflen) == -1)
    fatal_error(errno, "write(fifo)");

  free(buf);
  close(fd);
  return 0;
}
