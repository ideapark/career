#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    const int max_line = 1024;
    char line[max_line];
    while (cin.get(line, max_line)) {
        int get_count = cin.gcount();
        cout << "characters actually read: " << get_count << endl;
        if (get_count & max_line-1)
            cin.ignore();
    }
    return 0;
}
