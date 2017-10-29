// Jump.cpp -- using continue and break

#include <iostream>

const int ARRAY_SIZE = 80;

int main(void)
{
	using namespace std;

	char Line[ARRAY_SIZE];
	int Spaces = 0;

	cout << "Enter a line of text:\n";
	cin.get(Line, ARRAY_SIZE);
	cout << "Complete line:\n" << Line << endl;
	cout << "Line through first period:\n";
	for (int I = 0; Line[I] != '\0'; I++) {
		cout << Line[I];    // display character
		if (Line[I] == '.') // quit if it's a period
			break;
		if (Line[I] != ' ') // skip rest of loop
			continue;
		Spaces++;
	}
	cout << "\n" << Spaces << " spaces\n";
	cout << "Done.\n";

	return 0;
}
