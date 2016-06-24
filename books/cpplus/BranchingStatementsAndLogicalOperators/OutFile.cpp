// OutFile.cpp -- writing to a file

#include <iostream>
#include <fstream>   // for file I/O

int main(void)
{
    using namespace std;

    char AutoMobile[50];
    int Year;
    double APrice;
    double DPrice;

    ofstream OutFile;            // create object for output
    OutFile.open("carinfo.txt"); // associate with a file

    cout << "Enter the make and model of automobile: ";
    cin.getline(AutoMobile, 50);
    cout << "Enter the model year: ";
    cin >> Year;
    cout << "Enter the original asking price: ";
    cin >> APrice;
    DPrice = 0.913 * APrice;

    // display information on screen with cout
    cout << fixed;
    cout.precision(2);
    cout.setf(ios_base::showpoint);
    cout << "Make and model: " << AutoMobile << endl;
    cout << "Year: " << Year << endl;
    cout << "Was asking $" << APrice << endl;
    cout << "Was asking $" << DPrice << endl;

    // now do exat same things using OutFile instead of cout
    OutFile << fixed;
    OutFile.precision(2);
    OutFile.setf(ios_base::showpoint);
    OutFile << "Make and model: " << AutoMobile << endl;
    OutFile << "Year: " << Year << endl;
    OutFile << "Was asking $" << APrice << endl;
    OutFile << "Was asking $" << DPrice << endl;

    OutFile.close(); // done with file

    return 0;
}
