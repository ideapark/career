#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
#define MAXPATH 1024
    char sPath[MAXPATH] = { 0 }; /* init to zero */
    char *pTmp;

    if ((pTmp = getenv("PATH")) != NULL) {
        strncpy(sPath, pTmp, MAXPATH-1); /* bakup the result */
        printf("%s\n", pTmp);
    } else
        fprintf(stderr, "No PATH variable set.\n");

    return 0;
}
