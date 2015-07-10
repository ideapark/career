#include <algorithm>
#include <list>
#include <iostream>

using namespace std;

class Even {
public:
    bool operator()(int val) {
        return val % 2 ? false : true;
    }
};

int main(int argc, char *argv[])
{
    int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, };
    list<int> ilist(ia, ia+10);
    int ia_count = 0;
    ia_count = count_if(&ia[0], &ia[10], Even());
    cout << "count_if(): there are "
         << ia_count << " elements that are even.\n";
    int list_count = 0;
    list_count = count_if(ilist.begin(), ilist.end(), 
        bind2nd(less<int>(), 10));
    cout << "count_if(): there are "
         << list_count << " elements that are less than 10.\n";
    return 0;
}
