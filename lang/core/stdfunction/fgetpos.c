#include <stdio.h>

int main(void)
{
  FILE *datafile;
  fpos_t bookmark;

  if ((datafile = fopen("fgetpos.c", "r+")) == NULL) {
    fprintf(stderr, "Unable to open file %s.\n", "fgetpos.c");
    return 1;
  }

  if (fgetpos(datafile, &bookmark)) { /* store initial position */
    perror("Saving file position");
  } else {
    /* ... read/modify data ... */
    if (fsetpos(datafile, &bookmark)) /* return to bookmark position */
      perror("Restoring file position");
    /* ... write data to file initial position ... */
  }
  return 0;
}
