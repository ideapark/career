/*
 * Demonstrate glob().
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

char *myname;

/*
 * print error message for glob()
 */
int globerr(const char *path, int eerrno)
{
        fprintf(stderr, "%s: %s: %s\n", myname, path, strerror(eerrno));
        return 0; /* let glob() keep going */
}

/*
 * expand command-line wildcards and print results.
 */
int main(int argc, char *argv[])
{
        int i;
        int ret;
        int flags = 0;
        glob_t results;

        if (argc == 1) {
                fprintf(stderr, "usage: %s wildcard ...\n", argv[0]);
                exit(1);
        }

        myname = argv[0]; /* for globerr() */

        for (i = 1; i < argc; i++) {
                flags |= (i > 1 ? GLOB_APPEND: 0);
                ret = glob(argv[i], flags, globerr, &results);
                if (ret != 0) {
                        fprintf(stderr, "%s: problem with %s (%s), stopping early\n",
                                myname, argv[i],
                                (ret == GLOB_ABORTED ? "filesystem problem" :
                                 ret == GLOB_NOMATCH ? "no match of pattern" :
                                 ret == GLOB_NOSPACE ? "no dynamic memory" :
                                 "unknown problem")
                                );
                        break;
                }
        }

        for (i = 0; i < results.gl_pathc; i++)
                printf("%s\n", results.gl_pathv[i]);

        globfree(&results);
        return 0;
}
