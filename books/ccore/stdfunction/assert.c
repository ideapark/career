#include <assert.h>

int main(void)
{
    int units_in_stock = 10;
    int units_shipped = 9;
    /* ... */
    units_shipped++;
    units_in_stock--;
    /* ... */
    units_in_stock -= units_shipped;
    assert(units_in_stock >= 0);
    return 0;
}
