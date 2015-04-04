#include <stdio.h>

struct Date {
    unsigned int month : 4;   // 1: Jaunary, 12: december
    unsigned int day   : 5;   // days of month (1 ~ 31)
    signed int   year  : 22;  // (-2097152 ~ +2097151)
    _Bool        isDST : 1;   // True
};

const char* dateAsString(struct Date d)
{
    static char strDate[12];
    sprintf(strDate, "%02d/%02d/%04d", d.month, d.day, d.year);
    return strDate;
}

int main(void)
{
    struct Date birthday = { 5, 17, 1982 };
    puts(dateAsString(birthday));
    return 0;
}
