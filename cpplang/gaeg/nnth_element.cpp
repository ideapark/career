#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
    int ia[] = { 29, 23, 20, 22, 17, 15, 26, 51, 19, 12, 35, 40, };
    vector<int> vec(ia, ia+12);
    ostream_iterator<int> out(cout, " ");
    cout << "original order of the vector: ";
    copy(vec.begin(), vec.end(), out);
    cout << endl;

    cout << "sorting vector based on element "
        << *(vec.begin()+6) << endl;
    nth_element(vec.begin(), vec.begin()+6, vec.end());
    copy(vec.begin(), vec.end(), out);
    cout << endl;

    cout << "sorting vector in descending order "
        << "based on element "
        << *(vec.begin()+6) << endl;
    nth_element(vec.begin(), vec.begin()+6, vec.end(), greater<int>());
    copy(vec.begin(), vec.end(), out);
    cout << endl;
    return 0;
}
