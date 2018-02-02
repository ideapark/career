#include <math.h>
#include <stdio.h>

#define PI 3.141593
#define DEG_PER_RAD (180.0/PI)

int main(void)
{
  double adjacent = 3.0;
  double opposite = 4.0;
  double angle = atan2(opposite, adjacent) * DEG_PER_RAD;
  printf("The acute angles of 3-4-5 right triangle are %4.2f "
         "and %4.2f.\n", angle, 90.0-angle);
  return 0;
}
