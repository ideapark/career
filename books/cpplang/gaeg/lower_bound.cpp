#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int ia[] = { 29, 23, 20, 22, 17, 15, 26, 51, 19, 12, 35, 40, };
    sort(&ia[0], &ia[12]);
    int search_value = 18;
    int *ptr = lower_bound(ia, ia+12, search_value);
    cout << "The first element "
        << search_value
        << " can be inserted in front of is "
        << *ptr << endl
        << "The previous value is "
        << *(ptr-1) << endl;
    vector<int> ivec(ia, ia+12);
    sort(ivec.begin(), ivec.end(), greater<int>());
    search_value = 26;
    vector<int>::iterator iter;
    iter = lower_bound(ivec.begin(), ivec.end(), 
            search_value, greater<int>());
    cout << "The first element "
        << search_value
        << " can be inserted in front of is "
        << *iter << endl
        << "The previous value is "
        << *(iter-1) << endl;
    return 0;
}
