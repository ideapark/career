// CinGolf.cpp -- non-numeric input skipped

#include <iostream>

const int MAX = 5;

int main(void)
{
	using namespace std;

	// get data
	int Golf[MAX];
	cout << "Please enter your golf scores.\n";
	cout << "You must enter " << MAX << " rounds.\n";
	int I;
	for (I = 0; I < MAX; I++) {
		cout << "round #" << I+1 << ": ";
		while (!(cin >> Golf[I])) {
			cin.clear();
			while (cin.get() != '\n')
				continue; // get rid of bad input
			cout << "Please enter a number: ";
		}
	}

	// calculate average
	double Total = 0.0;
	for (I = 0; I < MAX; I++)
		Total += Golf[I];

	// report results
	cout << Total/MAX << " = average score " << MAX << " rounds\n";
	return 0;
}
