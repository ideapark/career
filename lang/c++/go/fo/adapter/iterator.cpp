#include <iterator>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

/*
 * Input:
 * 23 109 45 89 6 34 12 90 34 23 56 23 8 89 23
 *
 * Output:
 * 109 90 89 56 45 34 23 12 8 6
 */

int main() {
	std::istream_iterator<int> input(std::cin);
	std::istream_iterator<int> end_of_stream;
	std::vector<int> vec;

	std::copy(input, end_of_stream, std::inserter(vec, vec.begin()));
	std::sort(vec.begin(), vec.end(), std::greater<int>());

	std::ostream_iterator<int> output(std::cout, " ");
	std::unique_copy(vec.begin(), vec.end(), output);

	return 0;
}
