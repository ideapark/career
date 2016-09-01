#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

char *vstrcat(const char *first, ...)
{
        size_t len;
        char *retbuf;
        va_list argp;
        char *p;

        if (first == NULL)
                return NULL;

        len = strlen(first);

        va_start(argp, first);
        while ((p = va_arg(argp, char *)) != NULL)
                len += strlen(p);
        va_end(argp);

        retbuf = malloc(len + 1);

        if (retbuf == NULL)
                return NULL;

        (void)strcpy(retbuf, first);

        va_start(argp, first);
        while ((p = va_arg(argp, char *)) != NULL)
                (void)strcat(retbuf, p);
        va_end(argp);

        return retbuf;
}

int main(void)
{
        char *hello = vstrcat("Hello", ", ", "World", "!", NULL);
        printf("%s\n", hello);
        free(hello);

        char *proverb = vstrcat("A", " ", "quick", " ", "fox", " ",
                                "jumped", " ", "over", " ", "the", " ",
                                "lazy", " ", "dog", ".", NULL);
        printf("%s\n", proverb);
        free(proverb);

        return 0;
}
