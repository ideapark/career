// StringQuote.cpp -- different designs

#include <iostream>
#include <string>

using namespace std;

string Version1(const string &S1, const string &S2);
const string& Version2(string &S1, const string &S2); // has side effect
const string& Version3(string &S1, const string &S2); // bad design

int main(void)
{
	string Input;
	string Copy;
	string Result;

	cout << "Enter a string: ";
	getline(cin, Input);
	Copy = Input;
	cout << "Your string as entered: " << Input << endl;
	Result = Version1(Input, "***");
	cout << "Your string enhanced: " << Result << endl;
	cout << "Your original string: " << Input << endl;

	Result = Version2(Input, "###");
	cout << "Your string enhanced: " << Result << endl;
	cout << "Your original string: " << Input << endl;

	cout << "Resetting original string.\n";
	Input = Copy;
	Result = Version3(Input, "@@@");
	cout << "Your string enhanced: " << Result << endl;
	cout << "YOur original string: " << Input << endl;

	return 0;
}

string Version1(const string &S1, const string &S2)
{
	string Temp;
	Temp = S2 + S1 + S2;
	return Temp;
}

const string& Version2(string &S1, const string &S2)
{
	S1 = S2 + S1 + S2;
	// safe to return reference passed to function
	return S1;
}

// bad design
const string& Version3(string &S1, const string &S2)
{
	string Temp;
	Temp = S2 + S1 + S2;
	// unsafe to return reference to local variable
	return Temp;
}
