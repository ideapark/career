#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int ia[] = { 2, 3, 5, 8, };
    int ia2[] = { 1, 2, 3, 4, };
    int res = inner_product(&ia[0], &ia[4], &ia2[0], 0);
    cout << "inner product of arrays: " << res << endl;
    vector<int> vec(ia, ia+4);
    vector<int> vec2(ia2, ia2+4);
    res = inner_product(vec.begin(), vec.end(), vec2.begin(), 0, 
            minus<int>(), plus<int>());
    cout << "inner product of vectors: " << res << endl;
    return 0;
}
