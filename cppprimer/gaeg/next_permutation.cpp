#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void print_char(char elem) { cout << elem; }
void (*ppc)(char) = print_char;

int main(int argc, char *argv[])
{
    vector<char> vec(5);
    vec[0] = 'm';
    vec[1] = 'u';
    vec[2] = 's';
    vec[3] = 'i';
    vec[4] = 'l';
    int cnt = 2;
    sort(vec.begin(), vec.end());
    for_each(vec.begin(), vec.end(), ppc);
    cout << "\t";

    while (next_permutation(vec.begin(), vec.end())) {
        for_each(vec.begin(), vec.end(), ppc);
        cout << "\t";
        if (!(cnt++ % 8)) {
            cout << "\n";
            cnt = 1;
        }
    }
    cout << "\n\n";
    return 0;
}
