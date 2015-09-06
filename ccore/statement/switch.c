/*
 * switch menu
 */

#include <stdio.h>

int menu(void);
void action1(void),
     action2(void);

int main(void)
{
    switch (menu()) {
        case 'a':
        case 'A': action1(); break;
        case 'b':
        case 'B': action2(); break;
        default: putchar('\a');
    }
    return 0;
}

int menu(void)
{
    int choice;
    printf("Enter your choice please (Aa/Bb): ");
    choice = getchar();
    return choice;
}

void action1(void)
{
    printf("action #1\n");
}

void action2(void)
{
    printf("action #2\n");
}
