#include <time.h>
#include <stdio.h>

int main(void)
{
        time_t now;
        struct tm curtime;

        time(&now);
        curtime = *gmtime(&now);

        printf("%s", ctime(&now));
        printf("%s", asctime(&curtime));
        printf("%s", asctime(localtime(&now)));

        return 0;
}
