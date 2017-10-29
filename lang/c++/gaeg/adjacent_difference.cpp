#include <numeric>
#include <list>
#include <functional>
#include <iterator>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int ia[] = { 1, 1, 2, 3, 5, 8, };
	list<int> ilist(ia, ia+6);
	list<int> ilist_result(ilist.size());

	adjacent_difference(ilist.begin(), ilist.end(), ilist_result.begin());
	copy(ilist_result.begin(), ilist_result.end(),
	     ostream_iterator<int>(cout, " "));
	cout << endl;

	adjacent_difference(ilist.begin(), ilist.end(), ilist_result.begin(),
			    times<int>());
	copy(ilist_result.begin(), ilist_result.end(),
	     ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}
