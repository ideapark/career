// If.cpp -- using the if statement

#include <iostream>

int main(void)
{
	using std::cin; // using declarations
	using std::cout;

	char Ch;
	int Spaces = 0;
	int Total = 0;
	cin.get(Ch);
	while (Ch != '.') { // quit at end of sentence
		if (Ch == ' ')  // check if ch is space
			++Spaces;
		++Total;        // done every time
		cin.get(Ch);
	}
	cout << Spaces << " spaces, " << Total;
	cout << " characters total in sentence\n";

	return 0;
}
