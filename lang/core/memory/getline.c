#include <stdlib.h>
#include <stdio.h>

/*
 * Read a text line from stdin, put it in dynamic allocated buffer.
 * replace '\n' with '\0'.
 *
 * param: max line length
 * return: pointer to string readed;
 *         NULL if error occurred.
 */
char *getline(unsigned int len_max)
{
  char *linePtr = malloc(len_max+1);
  if (linePtr != NULL) {
    int c = EOF;
    unsigned int i = 0;
    while (i < len_max && (c = getchar()) != '\n' && c != EOF)
      linePtr[i++] = (char)c;
    linePtr[i] = '\0';
    if (c == EOF && i == 0) {
      free(linePtr);
      linePtr = NULL;
    } else {
      linePtr = realloc(linePtr, i+1); // adjust mem to best fit
    }
  }
  return linePtr;
}

int main(void)
{
  char *line;
  if ((line = getline(128)) != NULL) {
    puts(line);
    free(line);
  }
  return 0;
}
