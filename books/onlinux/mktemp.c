/*
 * Demonstrate naive use of mktemp().
 * error checking omitted for brevity
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

int main(void)
{
        static char template[] = "/tmp/myfileXXXXXX";
        char fname[PATH_MAX];
        static char mesg[] = "Here's lookin' at you, kid!\n"; /* beats "hello, world" */
        int fd;

        strcpy(fname, template);
        mktemp(fname);

        /* REACE CONDITION WINDOW OPENS */

        printf("Filename is %s\n", fname);

        /* REACE CONDITION WINDOW LASTS TO HERE */

        fd = open(fname, O_CREAT|O_RDWR|O_TRUNC, 0600);
        write(fd, mesg, strlen(mesg));
        close(fd);

        unlink(fname);

        return 0;
}
