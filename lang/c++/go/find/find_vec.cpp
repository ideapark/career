#include <algorithm>
#include <vector>
#include <iostream>

int main() {
	int search_value;
	int ia[6] = { 27, 210, 12, 47, 109, 83 };

	std::vector<int> vec(ia, ia+6);
	std::cout << "enter search value: ";
	std::cin >> search_value;

	std::vector<int>::iterator presult;
	presult = std::find(vec.begin(), vec.end(), search_value);

	std::cout << "The value "
		  << search_value
		  << (presult == vec.end() ? " is not present" : " is present")
		  << std::endl;

	return 0;
}
