// TwoFile2.cpp -- variables with internal and external linkage

#include <iostream>

extern int Tom;       // tom defined elsewhere
static int Dick = 10; // overrides external dick
int Harry = 200;      // external variable definition,
                      // no confilict with TwoFile2.cpp harry

void RemoteAccess()
{
    using namespace std;
    cout << "RemoteAccess() reports the following addresses:\n";
    cout << &Tom << " = &tom, " << &Dick << " = &dick, ";
    cout << &Harry << " = &harry\n";
}
