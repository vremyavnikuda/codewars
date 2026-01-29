#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <mqueue.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef BOOL
#define BOOL int
#define TRUE 1
#define FALSE 0
#endif

#define READ_END 0
#define WRITE_END 1

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

/*
 * Родитель: select() по STDIN и read-end pipe.
 * Ребёнок: mq_receive() в цикле и пересылка в pipe:
 *   [uint32_t len][uint32_t prio][payload...]
 */

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s /queue_name\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *qname = argv[1];

  mqd_t mqd = mq_open(qname, O_RDONLY);
  if (mqd == (mqd_t)-1)
    fatal_error(errno, "mq_open");

  struct mq_attr attr;
  if (mq_getattr(mqd, &attr) == -1)
    fatal_error(errno, "mq_getattr");

  size_t msgsize = (size_t)attr.mq_msgsize;
  if (msgsize == 0)
    fatal_error(-1, "mq_msgsize is 0");

  int pfd[2];
  if (pipe(pfd) == -1)
    fatal_error(errno, "pipe");

  pid_t child = fork();
  if (child == -1)
    fatal_error(errno, "fork");

  if (child == 0) {
    close(pfd[READ_END]);

    char *buf = calloc(1, msgsize + 1);
    if (!buf)
      fatal_error(errno, "calloc");

    for (;;) {
      unsigned int prio = 0;
      ssize_t n = mq_receive(mqd, buf, msgsize, &prio);
      if (n < 0) {
        if (errno == EINTR)
          continue;
        fatal_error(errno, "mq_receive");
      }

      uint32_t len32 = (uint32_t)n;
      uint32_t prio32 = (uint32_t)prio;

      if (write_full(pfd[WRITE_END], &len32, sizeof(len32)) == -1)
        fatal_error(errno, "write(pipe) len");
      if (write_full(pfd[WRITE_END], &prio32, sizeof(prio32)) == -1)
        fatal_error(errno, "write(pipe) prio");
      if (write_full(pfd[WRITE_END], buf, (size_t)n) == -1)
        fatal_error(errno, "write(pipe) payload");
    }
  }

  close(pfd[WRITE_END]);

  BOOL done = FALSE;
  while (!done) {
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);
    FD_SET(pfd[READ_END], &rfds);

    int maxfd = (STDIN_FILENO > pfd[READ_END]) ? STDIN_FILENO : pfd[READ_END];

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

    if (FD_ISSET(pfd[READ_END], &rfds)) {
      uint32_t len32 = 0, prio32 = 0;

      ssize_t r1 = read_full(pfd[READ_END], &len32, sizeof(len32));
      if (r1 == 0) {
        done = TRUE;
        continue;
      }
      if (r1 < 0)
        fatal_error(errno, "read(pipe) len");

      if (read_full(pfd[READ_END], &prio32, sizeof(prio32)) <= 0)
        fatal_error(errno, "read(pipe) prio");

      char *payload = calloc(1, (size_t)len32 + 1);
      if (!payload)
        fatal_error(errno, "calloc payload");

      if (read_full(pfd[READ_END], payload, (size_t)len32) <= 0)
        fatal_error(errno, "read(pipe) payload");

      printf("Received (%u bytes, prio=%u): %s\n", len32, prio32, payload);
      fflush(stdout);
      free(payload);
    }
  }

  kill(child, SIGTERM);
  (void)waitpid(child, NULL, 0);

  close(pfd[READ_END]);
  mq_close(mqd);
  return 0;
}
