#include <algorithm>
#include <list>
#include <string>
#include <iostream>
#include <iterator>

using namespace std;

class print_elements {
public:
    void operator()(string elem) {
        cout << elem << (_line_cnt++ % 8 ? " " : "\n\t");
    }
    static void reset_line_cnt() { _line_cnt = 1; }
private:
    static int _line_cnt;
};

int print_elements::_line_cnt = 1;

int main(int argc, char *argv[])
{
    string sa[] = {
        "Signature", "of", "all", "things", "I", 
        "am", "here", "to", "read", "seaspawn", 
        "and", "seawrack", "that", "rusty", "boot",
    };
    list<string> slist(sa, sa+15);
    cout << "Original sequence of strings:\n\t";
    for_each(slist.begin(), slist.end(), print_elements());
    cout << "\n\n";
    reverse(slist.begin(), slist.end());
    print_elements::reset_line_cnt();
    cout << "Sequence after reverse() applied:\n\t";
    for_each(slist.begin(), slist.end(), print_elements());
    cout << "\n";
    list<string> slist_copy(slist.size());
    reverse_copy(slist.begin(), slist.end(), slist_copy.begin());
    return 0;
}
