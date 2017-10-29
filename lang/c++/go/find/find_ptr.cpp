/*
 * template <class ForwardIterator, class Type>
 * ForwardIterator find(ForwardIterator first, ForwardIterator last,
 *     Type value) {
 *   for (; first != last; ++first)
 *     if (value == *first)
 *        return first;
 *   return last;
 * }
 */

#include <algorithm>
#include <iostream>

int main() {
	int search_value;
	int ia[6] = { 27, 210, 12, 47, 109, 83 };

	std::cout << "enter search value: ";
	std::cin >> search_value;
	int *presult = std::find<int*>(&ia[0], &ia[6], search_value);

	std::cout << "The value "
		  << search_value
		  << (presult == &ia[6] ? " is not present" : "is present")
		  << std::endl;

	return 0;
}
