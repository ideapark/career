/*
 * the canonical first program, localized version.
 */
#include <stdio.h>
#include <locale.h>
#include <libintl.h>

int main(void)
{
    setlocale(LC_ALL, "");
    printf("%s\n", gettext("hello, world"));
    return 0;
}
