#include <stdio.h>

struct point {
	int x;
	int y;
	int z;
};

int main(int argc, char *argv[])
{
	struct point p = {.x=3, .y=4, .z=5};

	printf("POINT(x=%d, y=%d, z=%d)\n", p.x, p.y, p.z);

	return 0;
}
