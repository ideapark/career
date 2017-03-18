#include <algorithm>
#include <list>
#include <string>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
    const int value = 9;
    int ia[] = { 0, 1, 1, 2, 3, 5, 8, };
    ostream_iterator<int> ofile(cout, " ");
    cout << "original array element sequence:\n";
    copy(ia, ia+7, ofile);
    cout << "\n\n";

    fill(ia+1, ia+6, value);
    cout << "array after fill(ia+1, ia+6):\n";
    copy(ia, ia+7, ofile);
    cout << "\n\n";

    string the_lang("C++");
    string langs[5] = { "c", "eiffel", "java", "ada", "perl" };
    list<string> il(langs, langs+5);
    ostream_iterator<string> sofile(cout, " ");

    cout << "original list element sequence:\n";
    copy(il.begin(), il.end(), sofile);
    cout << "\n\n";

    typedef list<string>::iterator iterator;
    iterator ibegin = il.begin(), iend = il.end();
    fill(++ibegin, --iend, the_lang);
    cout << "list after fill(++begin, --iend):\n";
    copy(il.begin(), il.end(), sofile);
    cout << "\n\n";

    return 0;
}
