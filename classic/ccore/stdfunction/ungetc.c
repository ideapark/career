#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    char file[] = "./ungetc.c";
    FILE *fp;
    int c;
    char numstr[64];

    if ((fp = fopen(file, "r")) == NULL) {
        fprintf(stderr, "Can't read the file %s\n", file);
        exit(1);
    }

    while ((c = getc(fp)) != EOF) {
        if (isdigit(c)) { /* collect digits */
            int i = 0;
            do {
                numstr[i++] = (char)c;
                c = getc(fp);
            } while (isdigit(c) && i+1 < sizeof(numstr));
            numstr[i] = '\0'; /* terminating char */

            puts(numstr);

            if (ungetc(c, fp) == EOF) /* write first non-digit */
                break;
            continue;
        }
        /* ... handle non-digit char ... */
    }

    if (!feof(fp)) {
        fprintf(stderr, "Error processing the file %s\n", file);
    }

    return 0;
}
