/*
 * Demonstrate wordexp().
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <wordexp.h>

char *myname;

/*
 * print error message for glob()
 */
int globerr(const char *path, int eerrno)
{
	fprintf(stderr, "%s: %s: %s\n", myname, path, strerror(eerrno));
	return 0;		/* let glob() keep going */
}

/*
 * expand command-line wildcards and print results.
 */
int main(int argc, char *argv[])
{
	int i;
	int ret;
	int flags = 0;
	wordexp_t results;

	if (argc == 1) {
		fprintf(stderr, "usage: %s wildcard ...\n", argv[0]);
		exit(1);
	}

	myname = argv[0];	/* for globerr() */

	for (i = 1; i < argc; i++) {
		flags |= (i > 1 ? WRDE_APPEND : 0);
		ret = wordexp(argv[i], &results, flags);
		if (ret != 0) {
			fprintf(stderr,
				"%s: problem with %s (%s), stopping early\n",
				myname, argv[i],
				(ret ==
				 WRDE_BADCHAR ? "metacharacter invalid location"
				 : ret ==
				 WRDE_BADVAL ? "variable undefined" : ret ==
				 WRDE_CMDSUB ? "attempte to substitution" : ret
				 ==
				 WRDE_NOSPACE ? "memory allocating error" : ret
				 ==
				 WRDE_SYNTAX ? "shell syntax error" :
				 "unknown problem")
			    );
			break;
		}
	}

	for (i = 0; i < results.we_wordc; i++)
		printf("%s\n", results.we_wordv[i]);

	wordfree(&results);
	return 0;
}
