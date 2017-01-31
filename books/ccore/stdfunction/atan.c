#include <math.h>
#include <stdio.h>

int main(void)
{
#ifdef PI
        printf("The symbol PI was already defined.\n");
        long double pi = (long double)PI;
#else
        long double pi = 4.0L * atanl(1.0L); // tan(pi/4) = 1
#endif
        printf("Assume pi equals %.17Lf.\n", pi);
        return 0;
}
