#define _POSIX_C_SOURCE 200809L

#include <aio.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
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

static volatile sig_atomic_t timer_expired = 0;
static volatile sig_atomic_t input_ready = 0;

static void on_timer(int sig) {
  (void)sig;
  timer_expired = 1;
}

static void on_aio_complete(int sig, siginfo_t *si, void *ucontext) {
  (void)sig;
  (void)si;
  (void)ucontext;
  input_ready = 1;
}

static void moveto(int row, int col) {
  char buf[32];
  int n = snprintf(buf, sizeof(buf), "\033[%d;%dH", row, col);
  if (n > 0)
    (void)write(STDOUT_FILENO, buf, (size_t)n);
}

static void clear_screen(void) {
  const char *s = "\033[2J";
  (void)write(STDOUT_FILENO, s, strlen(s));
}

static void clear_to_eol(void) {
  const char *s = "\033[K";
  (void)write(STDOUT_FILENO, s, strlen(s));
}

static void get_window_size(int *rows, int *cols) {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_row > 0 &&
      ws.ws_col > 0) {
    *rows = ws.ws_row;
    *cols = ws.ws_col;
    return;
  }
  *rows = 24;
  *cols = 80;
}

static timer_t make_timer_usecs(long interval_usecs) {
  struct sigevent sev;
  memset(&sev, 0, sizeof(sev));
  sev.sigev_notify = SIGEV_SIGNAL;
  sev.sigev_signo = SIGUSR1;

  timer_t tid;
  if (timer_create(CLOCK_REALTIME, &sev, &tid) == -1)
    fatal_error(errno, "timer_create");

  struct itimerspec its;
  memset(&its, 0, sizeof(its));

  its.it_interval.tv_sec = interval_usecs / 1000000;
  its.it_interval.tv_nsec = (interval_usecs % 1000000) * 1000;
  its.it_value = its.it_interval;

  if (timer_settime(tid, 0, &its, NULL) == -1)
    fatal_error(errno, "timer_settime");

  return tid;
}

static void draw_sprite(int row, int col, char sprite) {
  moveto(row, col);
  (void)write(STDOUT_FILENO, &sprite, 1);
}

static void erase_sprite(int row, int col) {
  char blank = ' ';
  moveto(row, col);
  (void)write(STDOUT_FILENO, &blank, 1);
}

int main(void) {
  struct sigaction sa_timer;
  memset(&sa_timer, 0, sizeof(sa_timer));
  sa_timer.sa_handler = on_timer;
  sa_timer.sa_flags = SA_RESTART;
  sigemptyset(&sa_timer.sa_mask);
  if (sigaction(SIGUSR1, &sa_timer, NULL) == -1)
    fatal_error(errno, "sigaction(SIGUSR1)");

  struct sigaction sa_aio;
  memset(&sa_aio, 0, sizeof(sa_aio));
  sa_aio.sa_sigaction = on_aio_complete;
  sa_aio.sa_flags = SA_RESTART | SA_SIGINFO;
  sigemptyset(&sa_aio.sa_mask);
  if (sigaction(SIGIO, &sa_aio, NULL) == -1)
    fatal_error(errno, "sigaction(SIGIO)");

  int rows = 0, cols = 0;
  get_window_size(&rows, &cols);

  clear_screen();

  const char sprite = '*';
  int row = rows / 2;
  int col = 1;
  int prev_row = row;
  int prev_col = col;
  int row_adjust = 0;

  char inbuf[128];
  memset(inbuf, 0, sizeof(inbuf));

  struct aiocb in_cb;
  memset(&in_cb, 0, sizeof(in_cb));
  in_cb.aio_fildes = STDIN_FILENO;
  in_cb.aio_buf = inbuf;
  in_cb.aio_nbytes = sizeof(inbuf);
  in_cb.aio_offset = 0;
  in_cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
  in_cb.aio_sigevent.sigev_signo = SIGIO;

  if (aio_read(&in_cb) == -1)
    fatal_error(errno, "aio_read");

  timer_t tid = make_timer_usecs(50000);

  BOOL finished = FALSE;
  draw_sprite(row, col, sprite);

  while (!finished) {
    pause();

    if (input_ready) {
      input_ready = 0;

      int err = aio_error(&in_cb);
      if (err == 0) {
        ssize_t n = aio_return(&in_cb);

        if (n > 0) {
          for (ssize_t i = 0; i < n && !finished; i++) {
            char ch = inbuf[i];

            if (ch == 'q')
              finished = TRUE;
            else if (ch == 'u')
              row_adjust--;
            else if (ch == 'd')
              row_adjust++;

            if (ch != '\n') {
              char msg[128];
              int m = snprintf(msg, sizeof(msg), "Last input: %c", ch);
              moveto(rows, 1);
              clear_to_eol();
              if (m > 0)
                (void)write(STDOUT_FILENO, msg, (size_t)m);
            }
          }
        }

        memset(inbuf, 0, sizeof(inbuf));
        memset(&in_cb, 0, sizeof(in_cb));
        in_cb.aio_fildes = STDIN_FILENO;
        in_cb.aio_buf = inbuf;
        in_cb.aio_nbytes = sizeof(inbuf);
        in_cb.aio_offset = 0;
        in_cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
        in_cb.aio_sigevent.sigev_signo = SIGIO;

        if (!finished) {
          if (aio_read(&in_cb) == -1)
            fatal_error(errno, "aio_read");
        }
      } else if (err != EINPROGRESS) {
        errno = err;
        fatal_error(errno, "aio_error");
      }
    }

    if (timer_expired) {
      timer_expired = 0;

      row += row_adjust;
      row_adjust = 0;

      if (row < 1)
        row = 1;
      if (row > rows - 1)
        row = rows - 1;

      col++;
      if (col > cols)
        col = 1;

      erase_sprite(prev_row, prev_col);
      draw_sprite(row, col, sprite);

      prev_row = row;
      prev_col = col;
    }
  }

  moveto(rows, 1);
  clear_to_eol();
  (void)write(STDOUT_FILENO, "\n", 1);

  aio_cancel(STDIN_FILENO, &in_cb);
  timer_delete(tid);
  return 0;
}
