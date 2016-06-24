#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int ia[] = { 0, 1, 1, 3, 5, 8, 13 };
    vector<int> vec(ia, ia+7);
    ostream_iterator<int> ofile(cout, " ");
    cout << "original element sequence:\n";
    copy(vec.begin(), vec.end(), ofile);
    cout << '\n';
    copy(ia+1, ia+7, ia);
    cout << "shifting array sequence left by 1:\n";
    copy(ia, ia+7, ofile);
    cout << '\n';
    copy(vec.begin()+2, vec.end(), vec.begin());
    cout << "shifting vector sequence left by 2:\n";
    copy(vec.begin(), vec.end(), ofile);
    cout << '\n';
    return 0;
}
