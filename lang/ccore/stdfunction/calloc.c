#include <stdlib.h>
#include <stdio.h>

int main(void)
{
        size_t n;
        int *p;
        printf("\nHow many integers do you want to enter? ");
        scanf("%u", &n);
        p = (int*)calloc(n, sizeof(int)); /* alloc memory */
        if (p == NULL)
                printf("\nInsufficient memory.");
        else
                NULL; /* read data to array */
        free(p);  /* free memory, avoiding dangling pointer */
        p = NULL;
        return 0;
}
