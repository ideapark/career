#ifndef F_MATH_INCLUDE_
#define F_MATH_INCLUDE_

int gcd(int v1, int v2);
int rgcd(int v1, int v2);

inline int abs(int i) {
	return (i < 0 ? -i : i);
}

inline int min(int v1, int v2) {
	return (v1 < v2 ? v1 : v2);
}

#endif // F_MATH_INCLUDE_
