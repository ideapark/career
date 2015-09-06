#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    printf("Think of a number between one and twenty.\n"
           "Press Enter when you're ready.");
    getchar();
    srand((unsigned)time(NULL));

    for (int i = 0; i < 3; i++) {
        printf("Is it %u? (y or n)", 1+rand()%20);
        if (tolower(getchar()) == 'y') {
            printf("Ha! I knew it!\n");
            exit(0);
        }
        getchar(); /* discard '\n' */
    }
    printf("I give up.\n");

    return 0;
}
