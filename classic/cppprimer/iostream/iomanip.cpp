#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    char ch;
    int tab_cnt = 0, nl_cnt = 0, space_cnt = 0,
        period_cnt = 0, comma_cnt = 0;
    while (cin.get(ch)) {
        switch (ch) {
            case ' ' : space_cnt++; break;
            case '\t': tab_cnt++; break;
            case '\n': nl_cnt++; break;
            case '.' : period_cnt++; break;
            case ',' : comma_cnt++; break;
        }
        cout.put(ch);
    }
    cout << "\nour statistics:\n\t"
        << "spaces: " << space_cnt << '\t'
        << "new lines: " << nl_cnt << "\t"
        << "tabs: " << tab_cnt << "\n\t"
        << "periods: " << period_cnt << '\t'
        << "commas: " << comma_cnt << endl;
    return 0;
}
