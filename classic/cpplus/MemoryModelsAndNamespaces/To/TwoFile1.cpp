// TwoFile1.cpp -- variables with external and internal linkage

#include <iostream> // to be compiled with two file2.cpp

int Tom = 3;        // external variable definition
int Dick = 30;      // external variable definition

static int Harry = 300; // static, internal linkage

// function prototype
void RemoteAccess();

int main(void)
{
    using namespace std;
    cout << "main() reports the following addresses:\n";
    cout << &Tom << " = &tom, " << &Dick << " = &dick, ";
    cout << &Harry << " = &harry\n";
    RemoteAccess();
    return 0;
}
