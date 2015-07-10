#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    string s_array[] = { "Ee", "eE", "ee", "Oo", "oo", "ee" };
    string to_find[] = { "oo", "gg", "ee" };

    string *found_it = find_first_of(s_array, s_array+6, 
            to_find, to_find+3);
    if (found_it != &s_array[6])
        cout << "found it: " << *found_it << "\n\t"
            << "&s_array[2]:\t" << &s_array[2] << "\n\t"
            << "&found_it:\t" << found_it << "\n\n";
    vector<string> svec(s_array, s_array+6);
    vector<string> svec_find(to_find, to_find+3);
    vector<string>::iterator found_it2;
    found_it2 = find_first_of(svec.begin(), svec.end(), svec_find.begin(),
            svec_find.end(), equal_to<string>());
    if (found_it2 != svec.end())
        cout << "found it, too: " << *found_it2 << "\n\t"
            << "svec.end()-2:\t" << *(svec.end()-2) << "\n\t"
            << "found_it2:\t" << *found_it2 << "\n";
    return 0;
}
