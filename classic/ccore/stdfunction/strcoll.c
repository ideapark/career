#include <string.h>
#include <stdio.h>
#include <locale.h>

int main(void)
{
    char *samples[] = { "curso", "churro" };

    setlocale(LC_COLLATE, "en_US.UTF-8");

    int result = strcoll(samples[0], samples[1]);

    if (result == 0)
        printf("The strings \"%s\" and \"%s\" are alphabetically equivalent.\n",
                samples[0], samples[1]);
    else if (result < 0)
        printf("The string \"%s\" and \"%s\" comes before alphabetically.\n",
                samples[0], samples[1]);
    else if (result > 0)
        printf("The string \"%s\" comes after \"%s\" alphabetically.\n",
                samples[0], samples[1]);

    return 0;
}
