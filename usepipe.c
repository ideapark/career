#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    static const char mesg[] = "Don't Panic!"; /* a famous message */
    char buf[BUFSIZ];
    ssize_t rcount, wcount;
    int pipefd[2];
    size_t len;

    if (pipe(pipefd) < 0) {
        fprintf(stderr, "%s: pipe failed: %s\n", argv[0],
                strerror(errno));
        exit(1);
    }

    printf("Read end = fd %d, write end = fd %d\n",
            pipefd[0], pipefd[1]);

    len = strlen(mesg);

    if ((wcount = write(pipefd[1], mesg, len)) != len) {
        fprintf(stderr, "%s: write failed: %s\n", argv[0],
                strerror(errno));
        exit(1);
    }

    if ((rcount = read(pipefd[0], buf, BUFSIZ)) != wcount) {
        fprintf(stderr, "%s: read failed: %s\n", argv[0],
                strerror(errno));
        exit(1);
    }

    buf[rcount] = '\0';

    printf("Read <%s> from pipe\n", buf);
    (void)close(pipefd[0]);
    (void)close(pipefd[1]);

    return 0;
}
