#include <string.h>
#include <stdio.h>

int main(void)
{
    char *path = "/usr/local/bin:/usr/bin:/usr/bin/X11:/usr/games";
    int separator;
    char *basename = "aprogram";
    char fullname[1024] = "";

    separator = strcspn(path, ":"); /* index of first colon */
    strncpy(fullname, path, separator);
    fullname[separator] = '\0'; /* string tailing char */
    strncat(fullname, "/", sizeof(fullname)-strlen(fullname)-1);
    strncat(fullname, basename, sizeof(fullname)-strlen(fullname)-1);
    puts(fullname);

    return 0;
}
