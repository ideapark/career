#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> vec;
    for (int ix = 0; ix < 20; ix++)
        vec.push_back(ix);
    random_shuffle(vec.begin(), vec.end());
    cout << "random_shuffle of sequence of values 1 .. 20:\n";
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    return 0;
}
