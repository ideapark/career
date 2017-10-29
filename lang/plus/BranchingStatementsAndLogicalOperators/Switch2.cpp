// Switch.cpp -- using the switch statement

#include <iostream>

using namespace std;

void ShowMenu(); // function prototypes
void Report();
void Comfort();

int main(void)
{
	ShowMenu();
	char Choice;
	cin >> Choice;
	while (Choice != 'Q' && Choice != 'q') {
		switch (Choice) {
		case 'a':
		case 'A':
			cout << "\a\n";
			break;
		case 'r':
		case 'R':
			Report();
			break;
		case 'l':
		case 'L':
			cout << "The boss was in all day.\n";
			break;
		case 'c':
		case 'C':
			Comfort();
			break;
		default: cout << "That's not a choice.\n";
		}
		ShowMenu();
		cin >> Choice;
	}
	cout << "Bye!\n";

	return 0;
}

void ShowMenu()
{
	cout << "Please enter a, r, l, c, or q:\n"
		"a) alarm        r) report\n"
		"l) alibi        c) comfort\n"
		"q) quit\n";
}

void Report()
{
	cout << "It's been an excellent week for business.\n"
		"Sales are up 120%. Expenses are down 35%.\n";
}

void Comfort()
{
	cout << "Your employees think you are the finest CEO\n"
		"in the industry. The board of directors think\n"
		"you are the finest CEO in the industry.\n";
}
