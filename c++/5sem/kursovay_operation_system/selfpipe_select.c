#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#ifndef BOOL
#define BOOL int
#define TRUE 1
#define FALSE 0
#endif

static void fatal_error(int err, const char *msg)
{
    if (err == 0) err = errno;
    fprintf(stderr, "%s: %s\n", msg, strerror(err));
    exit(EXIT_FAILURE);
}

static int spipe[2] = {-1, -1};

static void set_nonblock(int fd)
{
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        fatal_error(errno, "fcntl(F_GETFL)");
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
        fatal_error(errno, "fcntl(F_SETFL)");
}

static void on_sigint(int sig)
{
    (void)sig;
    const unsigned char b = 1;
    if (spipe[1] != -1)
        (void)write(spipe[1], &b, 1);
}

int main(void)
{
    if (pipe(spipe) == -1)
        fatal_error(errno, "pipe");

    set_nonblock(spipe[0]);
    set_nonblock(spipe[1]);

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = on_sigint;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1)
        fatal_error(errno, "sigaction(SIGINT)");

    BOOL done = FALSE;
    while (!done)
    {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);
        FD_SET(spipe[0], &rfds);

        int maxfd = (STDIN_FILENO > spipe[0]) ? STDIN_FILENO : spipe[0];

        int rc = select(maxfd + 1, &rfds, NULL, NULL, NULL);
        if (rc < 0)
        {
            if (errno == EINTR) continue;
            fatal_error(errno, "select");
        }

        if (FD_ISSET(spipe[0], &rfds))
        {
            unsigned char buf[64];
            for (;;)
            {
                ssize_t r = read(spipe[0], buf, sizeof(buf));
                if (r > 0)
                {
                    for (ssize_t i = 0; i < r; i++)
                        printf("CTRL-C received\n");
                    fflush(stdout);
                    continue;
                }
                if (r == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
                    break;
                if (r == -1 && errno == EINTR)
                    continue;
                break;
            }
        }

        if (FD_ISSET(STDIN_FILENO, &rfds))
        {
            char ch = 0;
            ssize_t r = read(STDIN_FILENO, &ch, 1);
            if (r > 0 && ch == 'q')
                done = TRUE;
        }
    }

    close(spipe[0]);
    close(spipe[1]);
    return 0;
}
