#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
	int value = 0;
	int ia[] = { 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, };
	vector<int> vec(ia, ia+10);
	ostream_iterator<int> ofile(cout, " ");
	vector<int>::iterator vec_iter;
	cout << "original vector sequence:\n";
	copy(vec.begin(), vec.end(), ofile);
	cout << '\n';

	vec_iter = remove(vec.begin(), vec.end(), value);
	cout << "vector after remove, whithout applying erase():\n";
	copy(vec.begin(), vec.end(), ofile);
	cout << '\n';

	vec.erase(vec_iter, vec.end());
	cout << "vector after erase():\n";
	copy(vec.begin(), vec.end(), ofile);
	cout << '\n';

	int ia2[5];
	vector<int> vec2(ia, ia+10);
	remove_copy(vec2.begin(), vec2.end(), ia2, value);
	cout << "array after remove_copy():\n";
	copy(ia2, ia2+5, ofile);
	cout << endl;

	return 0;
}
