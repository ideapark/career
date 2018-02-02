#include <ctype.h>
#include <stdio.h>
#include <locale.h>

int main(void)
{
  unsigned int c;
  printf("\nThe current locale for the 'is ...' functions is '%s'.\n",
         setlocale(LC_CTYPE, NULL));
  printf("Here is a table of the 'is ...' values for the characters"
         " from 0 to 127 in this locale:\n\n");
  for (c = 0; c < 128; c++) { /* Loop iteration for each table row. */
    if (c % 24 == 0) { /* repeat head every 24 line */
      printf("Code char alnum alpha blank cntrl digit graph lower"
             " print punct space upper xdigit\n");
      printf("---------------------------------------------------"
             "-------------------------------\n");
    }
    printf("%4u %4c %3c %5c %5c %5c %5c %5c %5c %5c %5c %5c %5c %5c\n",
           c,
           (isprint(c) ? c : ' '),
           (isalnum(c) ? 'X' : '-'),
           (isalpha(c) ? 'X' : '-'),
           (isblank(c) ? 'X' : '-'),
           (iscntrl(c) ? 'X' : '-'),
           (isdigit(c) ? 'X' : '-'),
           (isgraph(c) ? 'X' : '-'),
           (islower(c) ? 'X' : '-'),
           (isprint(c) ? 'X' : '-'),
           (ispunct(c) ? 'X' : '-'),
           (isspace(c) ? 'X' : '-'),
           (isupper(c) ? 'X' : '-'),
           (isxdigit(c) ? 'X' : '-')
           );
  }
  return 0;
}
