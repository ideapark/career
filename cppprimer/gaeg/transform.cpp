#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <iterator>

using namespace std;

int double_val(int val) { return val+val; }

int difference(int val1, int val2) {
    return abs(val1 - val2);
}

int main(int argc, char *argv[])
{
    int ia[] = { 3, 5, 8, 13, 21, };
    vector<int> vec(5);
    ostream_iterator<int> outfile(cout, " ");
    cout << "original array values: ";
    copy(ia, ia+5, outfile);
    cout << endl;
    cout << "transform each element by doubling: ";
    transform(ia, ia+5, vec.begin(), double_val);
    copy(vec.begin(), vec.end(), outfile);
    cout << endl;
    cout << "transform each element by difference: ";
    transform(ia, ia+5, vec.begin(), outfile, difference);
    cout << endl;
    return 0;
}
