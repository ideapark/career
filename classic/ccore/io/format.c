#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("1234567890123456\n");
    printf("%-10s %s\n", "Player", "Score");
    printf("%-10s %4d\n", "John", 120);
    printf("%-10s %4d\n", "Mary", 77);
    putchar('\n');

    int month = 5, day = 1, year = 1987;
    printf("Date of birth: %02d-%02d-%04d\n", month, day, year);
    putchar('\n');

    char str[] = "Variable field width";
    int width = 30;
    printf("%-*s!\n", width, str);
    putchar('\n');

    char *team[] = { "Vivian", "Tim", "Frank", "Sally" };
    char separator = ';';
    for (int i = 0; i < sizeof(team)/sizeof(char*); ++i)
        printf("%10s%c", team[i], separator);
    putchar('\n');

    char msg[] = "Every solution breeds new problems.";
    printf("%.14s\n", msg);
    printf("%20.14s\n", msg);
    printf("%.8s\n", msg+6);
    putchar('\n');

    printf("%4d %4o %4x %4X\n", 63, 63, 63, 63);
    putchar('\n');

    long bignumber = 100000L;
    unsigned long long hugenumber = 100000ULL * 100000ULL;
    printf("%ld %11X\n", bignumber, hugenumber);
    putchar('\n');

    double x = 12.34;
    printf("%f %e %E\n", x, x, x);
    putchar('\n');

    double value = 8.765;
    printf("Value: %.2f\n", value);
    printf("Integer value:\n"
            " Rounded:   %5.0f\n"
            " Truncated: %5d\n", value, (int)value);
    putchar('\n');
    
    long double xxl = expl(1000);
    printf("e to the power of 1000 is %.2Le\n", xxl);
    putchar('\n');

    int age = 0;
    char name[64] = "";
    printf("Please enter your first name and your age:\n");
    scanf("%s%d", name, &age);

    return 0;
}
