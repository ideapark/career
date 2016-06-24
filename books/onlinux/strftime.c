#include <stdio.h>
#include <time.h>

int main(void)
{
    char buf[100];
    time_t now;
    struct tm *curtime;

    time(&now);
    curtime = localtime(&now);
    (void)strftime(buf, sizeof(buf), "It is now %A, %B %d, %Y, %I:%M %p",
            curtime);
    printf("%s\n", buf);
    return 0;
}
