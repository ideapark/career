// CinFish.cpp -- non-numeric input terminates loop

#include <iostream>

const int MAX = 5;

int main(void)
{
	using namespace std;

	// get data
	double Fish[MAX];
	cout << "Please enter the weights of your fish.\n";
	cout << "You may enter up to " << MAX << " fish <q to terminate>.\n";
	cout << "fish #1: ";
	int I = 0;
	while (I < MAX && cin >> Fish[I]) {
		if (++I < MAX)
			cout << "fish #" << I+1 << ": ";
	}
	// calculate average
	double Total = 0.0;
	for (int J = 0; J < I; J++)
		Total += Fish[J];
	// report results
	if (I == 0)
		cout << "No fish\n";
	else
		cout << Total/I << " = average weight of " << I << " fish\n";
	cout << "Done.\n";

	return 0;
}
