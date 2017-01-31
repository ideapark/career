#include <time.h>
#include <stdio.h>

int main(void)
{
        time_t eventtime;
        time(&eventtime);
        fprintf(stderr, "%s: Error number %d occurred.\n",
                ctime(&eventtime), 10);
        return 0;
}
