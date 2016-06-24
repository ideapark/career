// strout.cpp -- incore formatting (output)

#include <string>
#include <sstream>
#include <iostream>

int main(void)
{
    using namespace std;

    ostringstream outstr;
    string hdisk;
    cout << "What's the name of your hard disk? ";
    getline(cin, hdisk);
    int cap;
    cout << "What's its capacity in GB? ";
    cin >> cap;
    // write formatted information to string stream
    outstr << "The hard disk " << hdisk << " has a capacity of "
           << cap << " gigabytes.\n";
    string result = outstr.str(); // save result
    cout << result;
    return 0;
}
