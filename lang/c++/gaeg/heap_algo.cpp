#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

template <class Type>
void print_elements(Type elem) {
    cout << elem << " ";
}

int main(int argc, char *argv[])
{
    int ia[] = { 29, 23, 20, 22, 17, 15, 26, 51, 19, 12, 35, 40, };
    vector<int> vec(ia, ia+12);
    make_heap(&ia[0], &ia[12]);
    void (*pfi)(int) = print_elements;
    for_each(ia, ia+12, pfi);
    cout << "\n\n";

    make_heap(vec.begin(), vec.end(), greater<int>());
    for_each(vec.begin(), vec.end(), pfi);
    cout << "\n\n";

    sort_heap(ia, ia+12);
    for_each(ia, ia+12, pfi);
    cout << "\n\n";

    vec.push_back(8);
    push_heap(vec.begin(), vec.end(), greater<int>());
    for_each(vec.begin(), vec.end(), pfi);
    cout << "\n\n";

    pop_heap(vec.begin(), vec.end(), greater<int>());
    for_each(vec.begin(), vec.end(), pfi);
    cout << "\n\n";

    return 0;
}
