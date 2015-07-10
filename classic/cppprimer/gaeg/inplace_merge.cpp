#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

template <class Type>
void print_elements(Type elem) {
    cout << elem << " ";
}

int main(int argc, char *argv[])
{
    int ia[] = { 
        29, 23, 20, 17, 15, 
        26, 51, 12, 35, 40, 
        74, 16, 54, 21, 44, 
        62, 10, 41, 65, 71,
    };
    vector<int> ivec(ia, ia+20);
    void (*pfi)(int) = print_elements;
    sort(&ia[0], &ia[10]);
    sort(&ia[10], &ia[20]);
    cout << "ia sorted into two sub-arrays: \n";
    for_each(ia, ia+20, pfi);
    cout << "\n\n";

    inplace_merge(ia, ia+10, ia+20);
    cout << "ia inplace_merge:\n";
    for_each(ia, ia+20, pfi);
    cout << "\n\n";

    sort(ivec.begin(), ivec.begin()+10, greater<int>());
    sort(ivec.begin()+10, ivec.end(), greater<int>());
    cout << "ivec sorted into two sub-vectors: \n";
    for_each(ivec.begin(), ivec.end(), pfi);
    cout << "\n\n";

    inplace_merge(ivec.begin(), ivec.begin()+10, 
            ivec.end(), greater<int>());
    cout << "ivec inplace_merge:\n";
    for_each(ivec.begin(), ivec.end(), pfi);
    cout << endl;

    return 0;
}
