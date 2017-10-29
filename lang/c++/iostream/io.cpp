#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	std::string in_string;
	std::cout << "Please enter your name: ";
	std::cin >> in_string;
	if (in_string.empty())
		std::cerr << "error: input string is empty!\n";
	else
		std::cout << "hell, " << in_string << "!\n";
	return 0;
}
