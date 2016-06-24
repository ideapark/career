#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
    int ia[] = { 29, 23, 20, 22, 12, 17, 15, 26, 51, 19, 12, 23, 35, 40, };
    vector<int> vec(ia, ia+14);
    ostream_iterator<int> ofile(cout, " ");
    cout << "original element sequence:\n";
    copy(vec.begin(), vec.end(), ofile);
    cout << '\n';
    stable_sort(&ia[0], &ia[14]);
    cout << "stable sort -- default ascending order:\n";
    copy(ia, ia+14, ofile);
    cout << '\n';
    stable_sort(vec.begin(), vec.end(), greater<int>());
    cout << "stable sort -- descending order:\n";
    copy(vec.begin(), vec.end(), ofile);
    cout << '\n';
    return 0;
}
