#include <stdlib.h>
#include <stdio.h>

int main(void)
{
        int amount = -1234;
        char currencysym[2] = "$";
        char sign[2] = "-";
        div_t dollarsandcents = { 0, 0 };

        if (amount >= 0)
                sign[0] = '\0';
        dollarsandcents = div(abs(amount), 100);
        printf("The balance is %s%s%d.%2d\n", sign, currencysym,
               dollarsandcents.quot, dollarsandcents.rem);
        return 0;
}
