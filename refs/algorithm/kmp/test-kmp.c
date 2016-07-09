#include <assert.h>

int main(void)
{
	const char *origin = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char *expect1 = "opqrst";
	const char *expect2 = "abcfik";
	const char *expect3 = "ABCDEF";
	const char *expect4 = "ABCFIK";

	assert(kmp_search(origin, expect1) > 0);
	assert(kmp_search(origin, expect2) < 0);
	assert(kmp_search(origin, expect3) > 0);
	assert(kmp_search(origin, expect4) < 0);

	return 0;
}
