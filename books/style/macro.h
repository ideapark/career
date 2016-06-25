#define LOOP(CODE) { \
	t0 = clock(); \
	for (i = 0; i < n; i++) { \
		CODE; \
	} \
	printf("%7d ", clock() - t0); \
}

LOOP(f1 = f2)
LOOP(f1 = f2 + f3)
LOOP(f1 = f2 - f3)
