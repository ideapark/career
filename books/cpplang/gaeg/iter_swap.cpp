#include <algorithm>
#include <list>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int ia[] = { 5, 4, 3, 2, 1, 0, };
    list<int> ilist(ia, ia+6);
    typedef list<int>::iterator iterator;
    iterator iter1 = ilist.begin(), iter2, iter_end = ilist.end();
    for ( ; iter1 != iter_end; ++iter1)
        for (iter2 = iter1; iter2 != iter_end; ++iter2)
            if (*iter2 < *iter1)
                iter_swap(iter1, iter2);
    cout << "ilist after bubble sort using iter_swap(): { ";
    for (iter1 = ilist.begin(); iter1 != iter_end; ++iter1)
        cout << *iter1 << " ";
    cout << "}\n";
    return 0;
}
