#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

class even_by_twos {
public:
	even_by_twos(int seed = 0) : _seed(seed) { }
	int operator()() { return _seed += 2; }
private:
	int _seed;
};

template <class Type>
void print_elements(Type elem) {
	cout << elem << " ";
}

int main(int argc, char *argv[])
{
	list<int> ilist(10);
	void (*pfi)(int) = print_elements;
	generate_n(ilist.begin(), ilist.size(), even_by_twos());
	cout << "generate_n with even_by_twos():\n";
	for_each(ilist.begin(), ilist.end(), pfi);
	cout << "\n";
	generate_n(ilist.begin(), ilist.size(), even_by_twos(100));
	cout << "generate_n with even_by_twos(100):\n";
	for_each(ilist.begin(), ilist.end(), pfi);
	return 0;
}
