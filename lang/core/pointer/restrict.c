double scalar_product(const double * restrict p1,
                      const double * restrict p2, int n)
{
  double result = 0.0;
  for (int i = 0; i < n; ++i)
    result += p1[i] * p2[i];
  return result;
}
