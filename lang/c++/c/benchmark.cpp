/**
 * Standard container performance test
 *
 *     std::list vs std::vector
 */

#include <list>
#include <vector>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <ctime>

void header(const char *header);
void content(const char *tip, clock_t list_clock, clock_t vector_clock);

int main() {
	std::list<int> ilist;
	std::list<std::string> slist;

	std::vector<int> ivec;
	std::vector<std::string> svec;

	const long cnt = 5000000;
	clock_t start = 0;
	clock_t end = 0;
	clock_t ldiff = 0;
	clock_t vdiff = 0;

	header("list vs vector : int vs string");

	start = std::clock();
	for (long ix = 0; ix < cnt; ix++)
		ilist.push_front(100);
	end = std::clock();
	ldiff = end - start;

	start = std::clock();
	for (long ix = 0; ix < cnt; ix++)
		ivec.push_back(100);
	end = std::clock();
	vdiff = end - start;

	content("list vs vector (int)", ldiff, vdiff);

	start = std::clock();
	for (long ix = 0; ix < cnt; ix++)
		slist.push_front("p@ctriple.cn");
	end = std::clock();
	ldiff = end - start;

	start = std::clock();
	for (long ix = 0; ix < cnt; ix++)
		svec.push_back("p@ctriple.cn");
	end = std::clock();
	vdiff = end - start;

	content("list vs vector (string)", ldiff, vdiff);

	return 0;
}

void header(const char *header) {
	std::cout << "----------------------------------------\n";
	std::cout << header << "\n";
	std::cout << "----------------------------------------\n";
}

void content(const char *tip, clock_t list, clock_t vector) {
	std::cout << std::setw(23) << tip << ":"
		  << std::setw(8) << list
		  << std::setw(8) << vector
		  << std::endl;
}
