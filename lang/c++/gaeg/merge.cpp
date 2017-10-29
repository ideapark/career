#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <iostream>

using namespace std;

template <class Type>
void print_elements(Type elem) {
	cout << elem << " ";
}

void (*pfi)(int) = print_elements;

int main(int argc, char *argv[])
{
	int ia[] = { 29, 23, 20, 22, 17, 15, 26, 51, 19, 12, 35, 40, };
	int ia2[] = { 74, 16, 39, 54, 21, 44, 62, 10, 27, 41, 65, 71, };
	vector<int> vec1(ia, ia+12);
	vector<int> vec2(ia2, ia2+12);
	int ia_result[24];
	vector<int> vec_result(vec1.size()+vec2.size());
	sort(ia, ia+12);
	sort(ia2, ia2+12);
	merge(ia, ia+12, ia2, ia2+12, ia_result);
	for_each(ia_result, ia_result+24, pfi);
	cout << "\n\n";
	sort(vec1.begin(), vec1.end(), greater<int>());
	sort(vec2.begin(), vec2.end(), greater<int>());
	merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
	      vec_result.begin(), greater<int>());
	for_each(vec_result.begin(), vec_result.end(), pfi);
	cout << "\n\n";
	return 0;
}
