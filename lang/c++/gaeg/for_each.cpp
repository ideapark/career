#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

template <class Type>
void print_elements(Type elem) {
	cout << elem << " ";
}

int main(int argc, char *argv[])
{
	vector<int> ivec;
	for (int ix = 0; ix < 10; ix++)
		ivec.push_back(ix);
	void (*pfi)(int) = print_elements;
	for_each(ivec.begin(), ivec.end(), pfi);
	return 0;
}
