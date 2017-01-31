#include <time.h>
#include <stdio.h>

static const char *const days[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday",
};

int main(void)
{
        time_t now;
        struct tm curtime;

        time(&now);
        curtime = *gmtime(&now); /* Both gmtime() and localtime() return a
                                    pointer to a struct tm. The pointer points
                                    to a static struct tm maintained by each
                                    routine, and is likely that these struct tm
                                    structures are overwritten each time the
                                    routines are called. Thus, it's a good idea
                                    to make a copy of the returned struct. */
        printf("Day of the week: %s\n", days[curtime.tm_wday]);

        return 0;
}
