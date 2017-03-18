#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BSIZE  256

int main(void)
{
    FILE *read_fp;
    char buffer[BSIZE+1];
    int chars_read;

    memset(buffer, '\0', sizeof(buffer));
    read_fp = popen("cat popen*.c | wc -l", "r");
    if (read_fp != NULL) {
        while ((chars_read = fread(buffer, sizeof(char), BSIZE, read_fp)) > 0) {
            buffer[chars_read-1] = '\0';
            printf("Reading %d:-\n %s \n", chars_read, buffer);
            sleep(1);
        }
        pclose(read_fp);
        exit(EXIT_SUCCESS);
    } else {
        fprintf(stderr, "popen() error.\n");
        exit(EXIT_FAILURE);
    }
}
