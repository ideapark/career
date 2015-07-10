#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
    int ia[] = { 29, 23, 20, 22, 17, 15, 26, 51, 19, 12, 35, 40, };

    vector<int> ivec(ia, ia+12);
    ostream_iterator<int> ofile(cout, " ");
    sort(&ia[0], &ia[12]);
    cout << "array element sequence after sort:\n";
    copy(ia, ia+12, ofile);
    cout << "\n\n";

    pair<int*, int*> ia_iter;
    ia_iter = equal_range(&ia[0], &ia[12], 23);
    cout << "equal_range result of search for value 23:\n\t"
        << "*ia_iter.first: " << *ia_iter.first << "\t"
        << "*ia_iter.second: " << *ia_iter.second << "\n\n";

    ia_iter = equal_range(&ia[0], &ia[12], 21);
    cout << "equal_range result of search for "
        << "absent value 21:\n\t"
        << "*ia_iter.first: " << *ia_iter.first << "\t"
        << "*ia_iter.second: " << *ia_iter.second << "\n\n";

    sort(ivec.begin(), ivec.end(), greater<int>());
    cout << "vector element sequence after sort:\n";
    copy(ivec.begin(), ivec.end(), ofile);
    cout << "\n\n";

    typedef vector<int>::iterator iter_ivec;
    pair<iter_ivec, iter_ivec> ivec_iter;
    ivec_iter = equal_range(ivec.begin(), ivec.end(), 26, greater<int>());
    cout << "equal_range result of search for value 26:\n\t"
        << "*ivec_iter.first: " << *ivec_iter.first << "\t"
        << "*ivec_iter.second: " << *ivec_iter.second << "\n\n";

    ivec_iter = equal_range(ivec.begin(), ivec.end(), 21, greater<int>());
    cout << "equal_range result of search for "
        << "absent value 21:\n\t"
        << "*ivec_iter.first: " << *ivec_iter.first << "\t"
        << "*ivec_iter.second: " << *ivec_iter.second << "\n\n";

    return 0;
}
