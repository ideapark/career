/*
 * KWP Search Algorithm
 */

#include <assert.h>
#include <string.h>

void kmp_table(const char *W, int *T)
{
	int pos = 2, cnd = 0, len;

	T[0] = -1;
	T[1] = 0;

	len = strlen(W);
	while (pos < len) {
		if (W[pos-1] == W[cnd]) {
			cnd++;
			T[pos] = cnd;
			pos++;
		} else if (cnd > 0) {
			cnd = T[cnd];
		} else {
			T[pos] = 0;
			pos++;
		}
	}
}

#define MAXWSIZE  256

int kmp_search(const char *S, const char *W)
{
	int m = 0, i = 0;
	int T[MAXWSIZE] = {0}, s_len, w_len;

	s_len = strlen(S);
	w_len = strlen(W);
	kmp_table(W, T);

	assert(w_len <= MAXWSIZE);

	while (m + i < s_len) {
		if (W[i] == S[m+i]) {
			if (i == (w_len-1))
				return m;
			else
				i++;
		} else {
			if (T[i] > -1) {
				m = m + i - T[i];
				i = T[i];
			} else {
				m++;
				i = 0;
			}
		}
	}
	return -1;
}
