#ifdef _DEBUG_
#include <assert.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define TITLE        "*** Examples of Macros Without Parameters ***"
#define BUFFER_SIZE  (4*512)
#define RANDOM       (-1.0+2.0*(double)rand()/RAND_MAX)
#define ARRAY_SIZE   10

#define printLog(...) fprintf(stderr, __VA_ARGS__)
