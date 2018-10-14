#include <math.h>
#include <stdio.h>

#define PI 3.141593
#define DEG_PER_RAD (180.0/PI)

int main(void)
{
	float height = 2.20F;
	float length = 1.23F;
	float altitude =
	    asinf(height / sqrtf(height * height + length * length));
	printf("The sun's altitude is %2.0f.\n", altitude * DEG_PER_RAD);
	return 0;
}
