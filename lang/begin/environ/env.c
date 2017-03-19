#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
        char *key, *value;
        if (argc == 1 || argc > 3) {
                fprintf(stderr, "usage: environ key [value]\n");
                exit(1);
        }
        key = argv[1];
        value = getenv(key);
        if (value)
                printf("Variable %s has value %s\n", key, value);
        else
                printf("Variable %s has no value\n", key);
        if (argc == 3) {
                char *string;
                value = argv[2];
                string = malloc(strlen(key)+strlen(value)+2);
                if (!string) {
                        fprintf(stderr, "out of memory\n");
                        exit(1);
                }
                strcpy(string, key);
                strcat(string, "=");
                strcat(string, value);
                printf("Calling putenv with: %s\n", string);
                if (putenv(string) != 0) {
                        fprintf(stderr, "putenv failed\n");
                        free(string);
                        exit(1);
                }
                value = getenv(key);
                if (value)
                        printf("New value of %s is %s\n", key, value);
                else
                        printf("New value of %s is null??\n", key);
        }
        return 0;
}
