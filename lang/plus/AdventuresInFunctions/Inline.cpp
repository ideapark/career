// Inline.cpp -- using an inline function

#include <iostream>

// an inline function definition
inline double Square(double X) { return X * X; }

int main(void)
{
	using namespace std;
	double A, B;
	double C = 13.0;
	A = Square(5.0);
	B = Square(4.5 + 7.5); // can pass expressions
	cout << "a = " << A << ", b = " << B << "\n";
	cout << "c = " << C;
	cout << ", c squared = " << Square(C++) << "\n";
	cout << "Now c = " << C << "\n";
	return 0;
}
