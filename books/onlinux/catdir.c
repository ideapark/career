#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

char *myname;
int process(char *dir);

int main(int argc, char *argv[])
{
    int i;
    int errors = 0;

    myname = argv[0];

    if (argc == 1)
        errors = process(".");
    else
        for (i = 1; i < argc; i++)
            errors += process(argv[i]);

    return (errors != 0);
}

int process(char *dir)
{
    DIR *dp;
    struct dirent *ent;

    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "%s: %s: cannot open for reading: %s\n",
                myname, dir, strerror(errno));
        return 1;
    }

    errno = 0;
    while ((ent = readdir(dp)) != NULL)
        printf("%8ld %s\n", ent->d_ino, ent->d_name);

    if (errno != 0) {
        fprintf(stderr, "%s: %s: reading directory entries: %s\n",
                myname, dir, strerror(errno));
        return 1;
    }

    if (closedir(dp) != 0) {
        fprintf(stderr, "%s: %s: closdir: %s\n",
                myname, dir, strerror(errno));
        return 1;
    }

    return 0;
}
