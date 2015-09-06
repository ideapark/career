// StrType1.cpp -- using the C++ string class

#include <iostream>
#include <string>   // make string class available

int main(void)
{
    using namespace std;

    char ChArr1[20];            // create an empty array
    char ChArr2[20] = "jaguar"; // create an initialized array
    string Str1;                // create an empty string object
    string Str2 = "panther";    // create an initialized string

    cout << "Enter a kind of feline: ";
    cin >> ChArr1;
    cout << "Enter another kind of feline: ";
    cin >> Str1; // use cin for input
    cout << "Here are some felines:\n";
    cout << ChArr1 << " " << ChArr2 << " "
         << Str1 << " " << Str2 // use cout for output
         << endl;
    cout << "The third letter in " << ChArr2 << " is "
         << ChArr2[2] << endl;
    cout << "The third letter in " << Str2 << " is "
         << Str2[2] << endl;    // use array notation

    return 0;
}
