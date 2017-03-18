/*
 * cylinderVolume: calc area of cylinder
 * r:   radius
 * h:   height
 * ret: area
 */
extern double cylinderVolume(double r, double h)
{
	const double pi = 3.1415926536;
	return pi * r * r * h;
}
