#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
    int ia[] = { 69, 23, 80, 42, 17, 15, 26, 51, 19, 12, 35, 8, };
    vector<int> vec(ia, ia+12);
    ostream_iterator<int> out(cout, " ");
    cout << "original order of vector: ";
    copy(vec.begin(), vec.end(), out);
    cout << endl;
    cout << "partial sort of vector: seven elemnts\n";
    partial_sort(vec.begin(), vec.begin()+7, vec.end());
    copy(vec.begin(), vec.end(), out);
    cout << endl;
    vector<int> res(7);
    cout << "partial_sort_copy() of first seven elements\n\t"
        << "of vector in descending order\n";
    partial_sort_copy(vec.begin(), vec.begin()+7, res.begin(), res.end(),
            greater<int>());
    copy(res.begin(), res.end(), out);
    cout << endl;
    return 0;
}
