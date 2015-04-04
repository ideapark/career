#include <stdio.h>

int main(void)
{
    FILE *fp;
    int c;

    if ((fp = fopen("infile.dat", "r")) == NULL)
        fprintf(stderr, "Couldn't open input file.\n");
    else {
        c = fgetc(fp);  // return char when succeed
        if (c == EOF) { // EOF: end of file
            if (feof(fp))
                fprintf(stderr, "End of input file reached.\n");
            else if (ferror(fp))
                fprintf(stderr, "Error on reading from input file.\n");
            clearerr(fp);
        } else {
            /* handle char */
        }
    }
    return 0;
}
