#include <stdio.h>

char *strcpy(char *s1, const char *s2)
{
        int i = 0;
        do {
                s1[i] = s2[i];
        } while (s2[i++] != '\0');
        return s1;
}

int main(void)
{
        char src[] = "Hello, World!";
        char dst[20]; //! ENSURE enough size
        printf("%s\n", strcpy(dst, src));
        return 0;
}
