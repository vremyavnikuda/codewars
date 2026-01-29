#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static volatile sig_atomic_t input_ready = 0;
static volatile sig_atomic_t count = 0;
static volatile sig_atomic_t last_si_fd = -1;
static volatile sig_atomic_t last_si_code = 0;

static void setup_fd(int fd) {
  int flagset = fcntl(fd, F_GETFL);
  if (flagset == -1)
    fatal_error(errno, "fcntl(F_GETFL)");

  if (fcntl(fd, F_SETFL, flagset | O_ASYNC | O_NONBLOCK) == -1)
    fatal_error(errno, "fcntl(F_SETFL)");

  if (fcntl(fd, F_SETOWN, getpid()) == -1)
    fatal_error(errno, "fcntl(F_SETOWN)");

  /* Просим ядро присылать SIGRTMIN вместо SIGIO (Linux-специфично) */
  if (fcntl(fd, F_SETSIG, SIGRTMIN) == -1)
    fatal_error(errno, "fcntl(F_SETSIG)");
}

static void on_input(int sig, siginfo_t *si, void *ucontext) {
  (void)sig;
  (void)ucontext;

  input_ready = 1;
  count++;

  if (si != NULL) {
    last_si_fd = si->si_fd;
    last_si_code = si->si_code;
  }
}

int main(void) {
  struct sigaction sigact;
  sigset_t blockedsigs;
  char ch;
  BOOL finished = FALSE;

  sigemptyset(&blockedsigs);
  sigaddset(&blockedsigs, SIGRTMIN);

  memset(&sigact, 0, sizeof(sigact));
  sigact.sa_sigaction = on_input;
  sigact.sa_flags = SA_RESTART | SA_SIGINFO;
  sigemptyset(&sigact.sa_mask);

  if (sigaction(SIGRTMIN, &sigact, NULL) == -1)
    fatal_error(errno, "sigaction(SIGRTMIN)");

  setup_fd(STDIN_FILENO);

  while (!finished) {
    pause();

    if (input_ready) {
      input_ready = 0;

      if (sigprocmask(SIG_BLOCK, &blockedsigs, NULL) == -1)
        fatal_error(errno, "sigprocmask(SIG_BLOCK)");

      while (read(STDIN_FILENO, &ch, 1) > 0 && !finished) {
        if (ch == 'q')
          finished = TRUE;

        printf("SIGRTMIN count = %d; current char = %c; si_fd = %d; si_code = "
               "%d\n",
               (int)count, ch, (int)last_si_fd, (int)last_si_code);
      }

      if (sigprocmask(SIG_UNBLOCK, &blockedsigs, NULL) == -1)
        fatal_error(errno, "sigprocmask(SIG_UNBLOCK)");
    }
  }

  return 0;
}
