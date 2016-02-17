#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
    int ia[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    int ia2[] = { 5, 6, 7, 8, 9, };
    vector<int> vec(ia, ia+10);
    vector<int> vec2(ia2, ia2+5);
    ostream_iterator<int> ofile(cout, " ");
    cout << "original element sequence of first container:\n";
    copy(vec.begin(), vec.end(), ofile);
    cout << '\n';
    copy(vec2.begin(), vec2.end(), ofile);
    cout << '\n';

    swap_ranges(&ia[0], &ia[5], &ia[5]);
    cout << "array after swap_ranges() in middle of array:\n";
    copy(ia, ia+10, ofile);
    cout << '\n';

    vector<int>::iterator last = find(vec.begin(), vec.end(), 5);
    swap_ranges(vec.begin(), last, vec2.begin());
    cout << "first container after "
        << "swap_ranges() of two vectors:\n";
    copy(vec.begin(), vec.end(), ofile);
    cout << '\n';
    cout << "second container after "
        << "swap_ranges() of two vectors:\n";
    copy(vec2.begin(), vec2.end(), ofile);
    cout << '\n';
    return 0;
}
