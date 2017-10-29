// LeftOver.cpp -- overloading the left() function

#include <iostream>

const int ARRAY_SIZE = 80;

unsigned long Left(unsigned long Num, unsigned CT);
char* Left(const char *Str, int N = 1);

int main(void)
{
	using namespace std;
	const char *Trip = "Hawaii!!"; // test value
	unsigned long N = 12345678;    // test value
	int I;
	char *Temp;
	for (I = 1; I < 10; I++) {
		cout << Left(N, I) << endl;
		Temp = Left(Trip, I);
		cout << Temp << endl;
		delete [] Temp; // point to temporary storage
	}
	return 0;
}


// this function returns the first ct digits of the number num.
unsigned long Left(unsigned long Num, unsigned CT)
{
	unsigned Digits = 1;
	unsigned long N = Num;
	if (CT == 0 || Num == 0)
		return 0; // return 0 if no digits
	while (N /= 10)
		Digits++;
	if (Digits > CT) {
		CT = Digits - CT;
		while (CT--)
			Num /= 10;
		return Num; // return left ct digits
	} else {
		return Num; // if ct >= number of digits
		// return the whole number
	}
}

// this function returns a pointer to a new string
// consisting of the first n characters in the str string.
char* Left(const char *Str, int N)
{
	if (N < 0) N = 0;
	char *P = new char[N+1];
	int I;
	for (I = 0; I < N && Str[I]; I++)
		P[I] = Str[I]; // copy characters
	while (I <= N)
		P[I++] = '\0'; // set rest of string to '\0'
	return P;
}
