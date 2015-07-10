// IfIf.cpp -- test for If-If performance

#include <iostream>

int main(void)
{
    using namespace std;

    char Ch;
    int Spaces = 0;
    int NewLines = 0;

    while (cin.get(Ch)) { // quit on eof
        if (Ch == ' ')
            Spaces++;
        if (Ch == '\n')
            NewLines++;
    }

    return 0;
}
