#include <stdio.h>
#include <wchar.h>

int main(void)
{
    wchar_t low_table[128];
    for (int i = 0; i < 128; i++)
        low_table[i] = (wchar_t)btowc(i);
    for (int i = 0; i < 128; i++)
        wprintf(L"%c ", low_table[i]);
    return 0;
}
