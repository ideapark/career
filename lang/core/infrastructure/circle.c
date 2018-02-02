// circle.c: output area of circle
//

#include <stdio.h>             // preprocessor

double circularArea(double r); // function declaration

int main()
{
  double radius = 1.0, area = 0.0;

  printf("       Areas of Circles\n\n");
  printf("         Radius     Area\n"
         "------------------------\n");

  area = circularArea(radius);
  printf("%10.1f    %10.2f\n", radius, area);

  radius = 5.0;
  area = circularArea(radius);
  printf("%10.1f    %10.2f\n", radius, area);

  return 0;
}

// circularArea() -- calculate area of circle
//
// parm:
//         radius of circle
// return:
//         area of circle
double circularArea(double r)
{
  const double pi = 3.1415926536; // constant value pi
  return pi * r * r;
}
