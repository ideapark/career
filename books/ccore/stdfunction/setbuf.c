#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = tmpfile();
    char *iobuffer = malloc(BUFSIZ);

    if (iobuffer != NULL) {
        /* NOTE:
         *       setbuf should be called after file open 
         *       successfull and before any I/O operation 
         *       occur
         */
        setbuf(fp, iobuffer); /* ensure temp file have a buffer */
    }

    /* use temp file */

    fclose(fp);
    return 0;
}
