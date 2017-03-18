#include <algorithm>
#include <list>
#include <iostream>

using namespace std;

class equal_and_odd {
public:
    bool operator()(int val1, int val2) {
        return (val1 == val2 && (val1 == 0 || val1 % 2));
    }
};

int main(int argc, char *argv[])
{
    int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, };
    int ia2[] = { 0, 1, 1, 2, 3, 5, 8, 13, 31, 34, };
    bool res;

    res = equal(&ia[0], &ia[7], &ia2[0]);
    cout << "int ia[7] equal to int ia2[9]? "
        << (res ? "true" : "false") << ".\n";

    list<int> ilist(ia, ia+7);
    list<int> ilist2(ia2, ia2+9);
    res = equal(ilist.begin(), ilist.end(), ilist2.begin());
    cout << "list ilist equal to ilist2? "
        << (res ? "true" : "false") << ".\n";

    res = equal(ilist.begin(), ilist.end(), ilist2.begin(), 
            equal_and_odd());
    cout << "list ilist equal_and_odd() to ilist2? "
        << (res ? "true" : "false") << ".\n";
    return 0;
}
