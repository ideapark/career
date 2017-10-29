#include <iostream>

int main() {
	const int *pci = new const int(1024);
	std::cout << "*pci = " << *pci << std::endl;

	// error: can NOT modify const
	// *pci = 512;

	return 0;
}
