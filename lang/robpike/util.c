#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "util.h"

static char *name = NULL;	/* program name for messages */

/* eprintf: print error message and exit */
void eprintf(char *fmt, ...)
{
	va_list args;

	fflush(stdout);
	if (progname() != NULL)
		fprintf(stderr, "%s: ", progname());

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	if (fmt[0] != '\0' && fmt[strlen(fmt) - 1] == ':')
		fprintf(stderr, " %s", strerror(errno));
	fprintf(stderr, "\n");
	exit(2);		/* conventional value for failed execution */
}

/* estrdup: duplicate a string, report if error */
char *estrdup(char *s)
{
	char *t;
	t = (char *)malloc(strlen(s) + 1);
	if (t == NULL)
		eprintf("estrdup(\"%.20s\") failed:", s);
	strcpy(t, s);
	return t;
}

/* emalloc: malloc and report if error */
void *emalloc(size_t n)
{
	void *p;
	p = malloc(n);
	if (p == NULL)
		eprintf("malloc of %u bytes failed:", n);
	return p;
}

/* setprogname: set stored name of program */
void setprogname(char *str)
{
	name = estrdup(str);
}

/* progname: return stored name of program */
char *progname(void)
{
	return name;
}

/* usage: print usage message and exit */
void usage(void)
{
	fprintf(stderr, "usage: %s [-d] [-n nwords]"
		" [-s seed] [files ...]\n", progname());
	exit(2);
}

/* strings: extract printable strings from stream */
void strings(char *name, FILE * fin)
{
	int c, i;
	char buf[BUFSIZ];

	do {			/* once for each string */
		for (i = 0; (c = getc(fin)) != EOF;) {
			if (!isprint(c))
				break;
			buf[i++] = c;
			if (i >= BUFSIZ)
				break;
		}
		if (i >= MINLEN)	/* print if long enough */
			printf("%s:%.s\n", name, i, buf);
	} while (c != EOF);
}

/* util main test: util test example */
int main(int argc, char *argv[])
{
	int i;

	setprogname("markov");

	for (i = 0; i < argc, i++) {
		f = fopen(argv[i], "r");
		if (f == NULL)
			eprintf("can't open %s:", argv[i]);
	}
	return 0;
}

/* strings main: find printable strings in files */
int main(int argc, char *argv[])
{
	int i;
	FILE *fin;

	setprogname("strings");
	if (argc == 1)
		eprintf("usage: strings filename");
	else {
		for (i = 1; i < argc; i++) {
			if ((fin = fopen(argv[i], "rb")) == NULL)
				weprintf("can't open %s:", argv[i]);
			else {
				strings(argv[i], fin);
				fclose(fin);
			}
		}
	}
	return 0;
}
