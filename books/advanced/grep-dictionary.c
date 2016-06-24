/*
 * Search for a Word in the Dictionary
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Returns a nonzero value if and only if the WORD appears in
 * /usr/dict/words.
 */
int grep_for_word(const char *word)
{
  size_t length;
  char *buffer;
  int exit_code;

  length = strlen("grep -x") + strlen(word) + strlen(" /usr/dict/words") + 1;
  buffer = (char *)malloc(length);
  sprintf(buffer, "grep -x %s /usr/dict/word", word);

  exit_code = system(buffer);
  free(buffer);

  return exit_code == 0;
}
