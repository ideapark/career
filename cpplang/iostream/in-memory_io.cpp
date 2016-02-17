#include <sstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    int ival = 1024;
    int *pival = &ival;
    double dval = 3.14159;
    double *pdval = &dval;
    ostringstream format_message;
    format_message << "ival: " << ival
        << " ival's address: " << pival << '\n'
        << "dval: " << dval
        << " dval's address: " << pdval << endl;
    string msg = format_message.str();
    cout << "sizeof message string: " << msg.size()
        << " message: " << msg << endl;
    return 0;
}
