#include <vector>
#include <string>
#include <iostream>
#include <iterator>

using std::cin;
using std::endl;
using std::cout;
using std::vector;
using std::string;
using std::istream_iterator;

int main() {
    istream_iterator<string> infile(cin);
    istream_iterator<string> eos;
    vector<string> svec(infile, eos);

    vector<string>::iterator iter = svec.begin();
    vector<string>::iterator iter_end = svec.end();
    while (iter != iter_end) {
        cout << *iter << endl;
        iter++;
    }

    return 0;
}
