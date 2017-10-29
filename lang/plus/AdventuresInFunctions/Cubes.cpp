// Cubes.cpp -- regular and reference arguments

#include <iostream>

double Cube(double A);
double RefCube(double &RA);

int main(void)
{
	using namespace std;
	double X = 3.0;
	cout << Cube(X);
	cout << " = cube of " << X << endl;
	cout << RefCube(X);
	cout << " = cube of " << X << endl;
	return 0;
}

double Cube(double A)
{
	A *= A*A;
	return A;
}

double RefCube(double &RA)
{
	RA *= RA * RA;
	return RA;
}
