// StrType2.cpp -- assigning, adding, and appending

#include <iostream>
#include <string>   // make string class available

int main(void)
{
    using namespace std;
    string S1 = "penguin";
    string S2, S3;

    cout << "You can assign one string object to another: S2 = S1\n";
    S2 = S1;
    cout << "S1: " << S1 << ", S2: " << S2 << endl;
    cout << "You can assign a C-style string to a string object.\n";
    cout << "S2 = \"buzzard\"\n";
    S2 = "buzzard";
    cout << "S2: " << S2 << endl;
    cout << "You can concatenate strings: S3 = S1 + S2\n";
    S3 = S1 + S2;
    cout << "S3: " << S3 << endl;
    cout << "You can append strings.\n";
    S1 += S2;
    cout << "S1 += S2 yields S1 = " << S1 << endl;
    S2 += " for a day";
    cout << "S2 += \" for a day\" yields S2 = " << S2 << endl;

    return 0;
}
