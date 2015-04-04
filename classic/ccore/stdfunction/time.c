#include <time.h>
#include <string.h>
#include <stdio.h>

#if 0
struct tm {
    int tm_sec;  /* seconds: 0~60 */
    int tm_min;  /* minutes: 0~59 */
    int tm_hour; /* hour: 0~23 */
    int tm_mday; /* day: 1~31 */
    int tm_mon;  /* month: 0~11 */
    int tm_year; /* year: from 1900 BC */
    int tm_wday; /* day of week: 0~6 (0 is sunday) */
    int tm_yday; /* day of year: 0~365 */
    int tm_isdst; /* daytime saving */
};
#endif

int main(void)
{
    time_t rawtime;
    struct tm utc_tm, local_tm, *ptr_tm;
    char buffer[1024] = "";

    time(&rawtime);
    ptr_tm = gmtime(&rawtime);
    memcpy(&utc_tm, ptr_tm, sizeof(struct tm));
    ptr_tm = localtime(&rawtime);
    memcpy(&local_tm, ptr_tm, sizeof(struct tm));

    if (strftime(buffer, sizeof(buffer), 
                "It's %A, %B %d, %Y, %R o'clock, UTC.", &utc_tm))
        puts(buffer);
    if (strftime(buffer, sizeof(buffer), 
                "Here it's %A, %B %d, %Y, %R o'clock, UTC %z.", &local_tm))
        puts(buffer);

    return 0;
}
