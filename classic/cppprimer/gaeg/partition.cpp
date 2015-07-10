#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

class even_elem {
public:
    bool operator()(int elem) {
        return elem % 2 ? false : true;
    }
};

int main(int argc, char *argv[])
{
    const int ia_size = 12;
    int ia[ia_size] = { 29, 23, 20, 22, 17, 15, 26, 51, 19, 12, 35, 40, };
    vector<int> vec(ia, ia+ia_size);
    ostream_iterator<int> outfile(cout, " ");
    cout << "original order of elements:\n";
    copy(vec.begin(), vec.end(), outfile);
    cout << endl;
    cout << "partition based on whether element is even:\n";
    partition(&ia[0], &ia[ia_size], even_elem());
    copy(ia, ia+ia_size, outfile);
    cout << endl;
    cout << "partition based on whether element "
        << "is less than 255:\n";
    partition(vec.begin(), vec.end(), bind2nd(less<int>(), 25));
    copy(vec.begin(), vec.end(), outfile);
    cout << endl;
    return 0;
}
