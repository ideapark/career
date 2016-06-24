#include <stdio.h>
#include <string.h>

int grep(FILE *fpIn, const char *keyword)
{
#define MAX_LINE 256
    char line[MAX_LINE] = "";
    int count = 0;
    if (fpIn == NULL || keyword == NULL)
        return -1;
    else
        rewind(fpIn);
    while (fgets(line, MAX_LINE, fpIn) != NULL) {
        if (strstr(line, keyword) != NULL) {
            ++count;
            fputs(line, stdout);
        }
    }
    if (!feof(fpIn))
        return -1;
    else
        return count;
}

int main(void)
{
    int cnt = grep(stdin, "Hello, world");
    return cnt > 0;
}
