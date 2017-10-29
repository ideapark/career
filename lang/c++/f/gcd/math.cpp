#include "math.h"

int gcd(int v1, int v2) {
	while (v2) {
		int temp = v2;
		v2 = v1 % v2;
		v1 = temp;
	}
	return v1;
}

int rgcd(int v1, int v2) {
	if (v2 != 0)
		return rgcd(v2, v1%v2);
	return v1;
}
