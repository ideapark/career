#include <algorithm>
#include <list>
#include <iostream>

int main() {
	int search_value;
	int ia[6] = { 27, 210, 12, 47, 109, 83 };

	std::list<int> list(ia, ia+6);
	std::cout << "enter search value: ";
	std::cin >> search_value;

	std::list<int>::iterator presult;
	presult = std::find(list.begin(), list.end(), search_value);

	std::cout << "The value "
		  << search_value
		  << (presult == list.end() ? " is not present" : " is present")
		  << std::endl;

	return 0;
}
