#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int c;

    if ((fp = fopen(argv[1], "r")) == NULL)
        fprintf(stderr, "Failed to open file %s\n", argv[1]);
    else {
        puts("Contents of the file in lower case:");
        while ((c = fgetc(fp)) != EOF)
            putchar(tolower(c));
        rewind(fp);
        puts("Same again in upper case:");
        while ((c = fgetc(fp)) != EOF)
            putchar(toupper(c));
        fclose(fp);
    }
    return 0;
}
