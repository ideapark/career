// FuncTemplate.cpp -- using a function template

#include <iostream>

// function template prototype
template <typename T> // or class T
void Swap(T &A, T &B);

int main(void)
{
	using namespace std;
	int I = 10;
	int J = 20;
	cout << "i, j = " << I << ", " << J << ".\n";
	cout << "Using compiler-generated int swapper:\n";
	Swap(I, J); // generates void Swap(int &, int &)
	cout << "Now i, j = " << I << ", " << J << ".\n";

	double X = 24.5;
	double Y = 81.7;
	cout << "x, y = " << X << ", " << Y << ".\n";
	cout << "Using compiler-generated double swapper:\n";
	Swap(X, Y); // generate void Swap(duble &, double &)
	cout << "Now x, y = " << X << ", " << Y << ".\n";
	return 0;
}

template <typename T> // or class T
void Swap(T &A, T &B)
{
	T Temp; // temp a variable of type T
	Temp = A;
	A = B;
	B = Temp;
}
