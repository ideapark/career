/* csv.h: interface for csv library */

#ifndef CSV_INCLUDE_
#define CSV_INCLUDE_

#include <stdio.h>

extern char* csvgetline(FILE* f); /* read next input line */
extern char* csvfield(int n);     /* return field n */
extern int csvnfield(void);       /* return number of fields */

enum {
	NOMEM = -2; /* out of memory signal */
};

#endif // CSV_INCLUDE_
