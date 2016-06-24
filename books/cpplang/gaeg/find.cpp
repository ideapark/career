#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    int array[17] = { 7, 3, 3, 7, 6, 5, 8, 7, 2, 1, 3, 8, 7, 3, 8, 4, 3, };
    int elem = array[9];
    int *found_it;
    found_it = find(&array[0], &array[7], elem);

    cout << "find the first occurrence of "
        << elem << "\t"
        << (found_it ? "found!\n" : "no found!\n");
    string beethoven[] = {
        "Sonata31", "Sonata32", "Quartet14",
        "Quartet15", "Archduke", "Symphony7",
    };
    string s_elem(beethoven[1]);
    list<string> slist(beethoven, beethoven+6);
    list<string>::iterator iter;
    iter = find(slist.begin(), slist.end(), s_elem);

    cout << "find the first occurrence of "
        << s_elem << "\t"
        << (iter != slist.end() ? "found!\n" : "not found!\n");
    return 0;
}
