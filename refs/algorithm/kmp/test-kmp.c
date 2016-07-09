#include <assert.h>

int main(void)
{
	const char *origin1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char *expect11 = "opqrst";
	const char *expect12 = "abcfik";
	const char *expect13 = "ABCDEF";
	const char *expect14 = "ABCFIK";

	assert(kmp_search(origin1, expect11) == 14);
	assert(kmp_search(origin1, expect12) == -1);
	assert(kmp_search(origin1, expect13) == 26);
	assert(kmp_search(origin1, expect14) == -1);

	const char *origin2 = "abcdabcdabcdabcdABCDABCDABCDABCD";
	const char *expect21 = "abcd";
	const char *expect22 = "abce";
	const char *expect23 = "ABCD";
	const char *expect24 = "ABCE";

	assert(kmp_search(origin2, expect21) == 0);
	assert(kmp_search(origin2, expect22) == -1);
	assert(kmp_search(origin2, expect23) == 16);
	assert(kmp_search(origin2, expect24) == -1);

	return 0;
}
