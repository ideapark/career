#include <algorithm>
#include <string>
#include <list>
#include <iterator>
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream infile("alice_emma");
    assert(infile != 0);
    list<string> textlines;

    typedef list<string>::difference_type diff_type;
    istream_iterator<string, diff_type> instream(infile), eos;
    copy(instream, eos, back_inserter(textlines));
    string search_item("fiery");
    int elem_count = 0;
    list<string>::iterator ibegin = textlines.begin(),
                           iend = textlines.end();
    elem_count = count(ibegin, iend, search_item);
    cout << "count(): " << search_item 
         << " occurs " << elem_count << " times\n";
    return 0;
}
