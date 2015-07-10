// StrType3.cpp -- more string class features

#include <iostream>
#include <string>   // make string class available
#include <cstring>  // C-style string library

int main(void)
{
    using namespace std;
    char ChArr1[20];
    char ChArr2[20] = "jaguar";
    string Str1;
    string Str2 = "panther";

    // assignment for string objects and character arrays
    Str1 = Str2;            // copy Str2 to Str1
    strcpy(ChArr1, ChArr2); // copy ChArr1 to ChArr2

    // appending for string objects and character arrays
    Str1 += " paste";         // add paste to end of Str1
    strcat(ChArr1, " juice"); // add juice to end of ChArr1

    // finding the length of a string object and a C-style string
    int Len1 = Str1.size();    // obtain length of Str1
    int Len2 = strlen(ChArr1); // obtain length of ChArr1

    cout << "The string " << Str1 << " contains " 
         << Len1 << " characters.\n";
    cout << "The string " << ChArr1 << " contains " 
         << Len2 << " characters.\n";

    return 0;
}
