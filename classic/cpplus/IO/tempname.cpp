// tempname.cpp -- generating distinct file name in the current directory

#include <cstdio>
#include <iostream>

int main(void)
{
    using namespace std;

    cout << "This system can generate up to " << TMP_MAX
         << " temporary names of up to " << L_tmpnam << " characters.\n";
    char pszName[L_tmpnam] = {'\0'};
    cout << "Here are " << TMP_MAX << " names:\n";
    for (int i = 0; i < TMP_MAX; i++) {
        tmpnam(pszName);
        cout << pszName << endl;
    }
    return 0;
}
