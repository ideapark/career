#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

struct person {
        char name[10]; /* first name */
        char id[10];   /* ID number */
        off_t pos;     /* position in file */
} people[] = {
        {"arnold", "123456789", 0},
        {"miriam", "987654321", 10240},
        {"joe", "192837465", 81920},
};

int main(int argc, char *argv[])
{
        int fd;
        int i, j;

        if (argc < 2) {
                fprintf(stderr, "usage: %s file\n", argv[0]);
                return 1;
        }

        fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0666);
        if (fd < 0) {
                fprintf(stderr, "%s: %s: connot open for read/write: %s\n",
                        argv[0], argv[1], strerror(errno));
                return 1;
        }

        j = sizeof(people) / sizeof(people[0]);

        for (i = 0; i < j; i++) {
                if (lseek(fd, people[i].pos, SEEK_SET) < 0) {
                        fprintf(stderr, "%s: %s: seek error: %s\n",
                                argv[0], argv[1], strerror(errno));
                        (void)close(fd);
                        return 1;
                }

                if (write(fd, &people[i], sizeof(people[i])) != sizeof(people[i])) {
                        fprintf(stderr, "%s: %s: write error: %s\n",
                                argv[0], argv[1], strerror(errno));
                        (void)close(fd);
                        return 1;
                }
        }

        (void)close(fd);
        return 0;
}
