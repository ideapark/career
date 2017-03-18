#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

string pooh_pals[] = {
    "Tigger", "Piglet", "Eeyore", "Rabbit",
};

int main(int argc, char *argv[])
{
    vector<string> ppals(pooh_pals, pooh_pals+4);
    vector<string>::iterator iter = ppals.begin(),
                             iter_end = ppals.end();
    cout << "These are Pooh's pals: ";
    ostream_iterator<string> output(cout, " ");
    copy(iter, iter_end, output);
    return 0;
}
