// SumFile.cpp -- functions with an array argument

#include <iostream>
#include <fstream> // file I/O support
#include <cstdlib> // support for exit()

const int SIZE = 60;

int main(void)
{
	using namespace std;

	char FileName[SIZE];
	ifstream InFile;         // object for handling file input
	cout << "Enter name of data file: ";
	cin.getline(FileName, SIZE);
	InFile.open(FileName);   // associate InFile with a file
	if (!InFile.is_open()) { // failed to open file
		cout << "Could not open the file " << FileName << endl;
		cout << "Program terminating.\n";
		exit(EXIT_FAILURE);
	}
	double Value;
	double Sum = 0;
	int Count = 0;   // number of items read
	InFile >> Value; // get first value
	while (InFile.good()) { // while input good and not at EOF
		++Count;         // one more item read
		Sum += Value;    // calculate running total
		InFile >> Value; // get next value
	}
	if (InFile.eof())
		cout << "End of file reached.\n";
	else if (InFile.fail())
		cout << "Input terminated by data mismatch.\n";
	else
		cout << "Input terminated for unknown reason.\n";
	if (Count == 0)
		cout << "No data processed.\n";
	else {
		cout << "Items read: " << Count << endl;
		cout << "Sum: " << Sum << endl;
		cout << "Average: " << Sum/Count << endl;
	}
	InFile.close(); // finished with the file

	return 0;
}
