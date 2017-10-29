#include <algorithm>
#include <list>
#include <iostream>

using namespace std;

int odd_by_twos() {
	static int seed = -1;
	return seed += 2;
}

template <class Type>
void print_elements(Type elem) {
	cout << elem << " ";
}

int main(int argc, char *argv[])
{
	list<int> ilist(10);
	void (*pfi)(int) = print_elements;
	generate(ilist.begin(), ilist.end(), odd_by_twos);
	cout << "elements within list the first invocation:\n";
	for_each(ilist.begin(), ilist.end(), pfi);
	generate(ilist.begin(), ilist.end(), odd_by_twos);
	cout << "\n\nelements within list the second iteration:\n";
	for_each(ilist.begin(), ilist.end(), pfi);
	return 0;
}
