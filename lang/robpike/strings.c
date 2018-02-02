#include <stdio.h>
#include <ctype.h>

#include "eprintf.h"

/* strings: extract printable strings from stream */
void strings(char *name, FILE *fin)
{
  int c, i;
  char buf[BUFSIZ];

  do {  /* once for each string */
    for (i = 0; (c = getc(fin)) != EOF; ) {
      if (!isprint(c))
        break;
      buf[i++] = c;
      if (i >= BUFSIZ)
        break;
    }
    if (i >= MINLEN) /* print if long enough */
      printf("%s:%.*s\n", name, i, buf);
  } while (c != EOF);
}

/* strings main: find printable strings in files */
int main(int argc, char *argv[])
{
  int i;
  FILE *fin;

  setprogname("strings");
  if (argc == 1)
    eprintf("usage: strings filenames");
  else {
    for (i = 1; i < argc; i++) {
      if ((fin = fopen(argv[i], "rb")) == NULL)
        weprintf("can't open %s:", argv[i]);
      esle {
        strings(argv[i], fin);
        close(fin);
      }
    }
  }
  return 0;
}
