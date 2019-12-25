#include <math.h>
#include <stdio.h>

#define PI 3.141593
#define DEG_PER_RAD (180.0/PI)

int main(void)
{
	double floor_width = 30.0;
	double roof_width = 34.6;
	double roof_pitch = acos(floor_width / roof_width) * DEG_PER_RAD;
	printf("The pitch of the roof is %2.0f degrees.\n", roof_pitch);
	return 0;
}
