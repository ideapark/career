#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
	std::ofstream outfile("out_file");
	std::ifstream infile("in_file");
	if (!infile) {
		std::cerr << "error: unable to open input file!\n";
		return -1;
	}
	if (!outfile) {
		std::cerr << "error: unable to open output file!\n";
		return -2;
	}
	std::string word;
	while (infile >> word)
		outfile << word << ' ';

	return 0;
}
