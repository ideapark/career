#include <algorithm>
#include <set>
#include <string>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
    string str1[] = { "Pooh", "Piglet", "Tigger", "Eyeore", };
    string str2[] = { "Pooh", "Heffalump", "Woozles", };
    ostream_iterator<string> ofile(cout, " ");
    set<string, less<string> > set1(str1, str1+4);
    set<string, less<string> > set2(str2, str2+3);

    cout << "set #1 elements:\n\t";
    copy(set1.begin(), set1.end(), ofile);

    cout << "\n\n";
    cout << "set #2 elements:\n\t";
    copy(set2.begin(), set2.end(), ofile);
    cout << "\n\n";

    set<string, less<string> > res;
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), 
            inserter(res, res.begin()));
    cout << "set_union() elements:\n\t";
    copy(res.begin(), res.end(), ofile);

    cout << "\n\n";
    res.clear();
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
            inserter(res, res.begin()));
    cout << "set_intersection() elements:\n\t";
    copy(res.begin(), res.end(), ofile);
    cout << "\n\n";

    res.clear();
    set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
            inserter(res, res.begin()));
    cout << "set_difference() elements:\n\t";
    copy(res.begin(), res.end(), ofile);
    cout << "\n\n";

    res.clear();
    set_symmetric_difference(set1.begin(), set1.end(), 
            set2.begin(), set2.end(), inserter(res, res.begin()));
    cout << "set_symmetric_differnece() elements:\n\t";
    copy(res.begin(), res.end(), ofile);
    cout << "\n\n";
    return 0;
}
