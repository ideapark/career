#include <stddef.h>

/*
 * The name DAXPY come from the formula itself: Double-precision A
 * times X Plus Y. The single-precision version is called SAXPY.
 *
 *        Y = a * X + Y
 *
 */
void daxpy(size_t n, double a, const double x[], double y[])
{
  for (size_t i = 0; i < n; i++) {
    y[i] = a*x[i] + y[i];
  }
}
