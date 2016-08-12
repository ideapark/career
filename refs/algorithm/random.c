#define a 16807
#define m 2147483647
#define q (m/a)
#define r (m%a)

static long int seed = 1;

long int rand(void)
{
	long int hi = seed / q;
	long int lo = seed % q;
	long int test = a * lo - r * hi;
	if (test > 0)
		seed = test;
	else
		seed = test + m;
	return seed;
}
