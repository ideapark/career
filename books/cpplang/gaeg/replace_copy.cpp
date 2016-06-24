#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
    string oldval("Mr. Winnie the Pooh");
    string newval("Pooh");
    ostream_iterator<string> ofile(cout, " ");
    string sa[] = {
        "Christopher Robin", "Mr. Winnie the Pooh",
        "Piglet", "Tigger", "Eyeore",
    };
    vector<string> vec(sa, sa+5);
    cout << "original element sequence:\n";
    copy(vec.begin(), vec.end(), ofile);
    cout << '\n';

    replace(vec.begin(), vec.end(), oldval, newval);
    cout << "sequence after applying replace():\n";
    copy(vec.begin(), vec.end(), ofile);
    cout << '\n';

    vector<string> vec2;
    replace_copy(vec.begin(), vec.end(), inserter(vec2, vec2.begin()),
            newval, oldval);
    cout << "sequence after applying replace_copy():\n";
    copy(vec2.begin(), vec2.end(), ofile);
    cout << '\n';

    return 0;
}
