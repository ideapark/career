#include <math.h>
#include <stdio.h>

struct point {
	int x;
	int y;
};

struct point scale(struct point orig)
{
	int width_orig = 1024;
	int height_orig = 768;
	int width_new = 800;
	int height_new = 600;

	struct point new;
	new.x = (int)floor(orig.x * (double)width_new/(double)width_orig);
	new.y = (int)floor(orig.y * (double)height_new/(double)height_orig);
	return new;
}

int main(void)
{
	struct point orig = { 10, 10 };
	struct point new = scale(orig);
	printf("Origin Point(%2d,%2d)\n", orig.x, orig.y);
	printf("Scaled Point(%2d,%2d)\n", new.x, new.y);
	return 0;
}
