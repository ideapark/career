// IfElse.cpp -- using the if else statement

#include <iostream>

int main(void)
{
	char Ch;
	std::cout << "Type, and I shall repeat.\n";
	std::cin.get(Ch);
	while (Ch != '.') {
		if (Ch == '\n')
			std::cout << Ch;   // done if newline
		else
			std::cout << ++Ch; // done otherwise
		std::cin.get(Ch);
	}
	// try Ch+1 instead of ++Ch for interesting effect
	std::cout << "\nPlease execuse the slight confusion.\n";
	// std::cin.get();
	// std::cin.get();
	return 0;
}
