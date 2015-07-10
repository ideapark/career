// UseNew.cpp -- using the new operator

#include <iostream>

int main(void)
{
    using namespace std;

    int Nights = 1001;
    int *Pt = new int; // allocate space for an int
    *Pt = 1001;        // store value there

    cout << "nights value = ";
    cout << Nights << ": location " << &Nights << endl;
    cout << "int ";
    cout << "value = " << *Pt << ": location = " << Pt << endl;

    double *Pd = new double; // allocate space for a double
    *Pd = 10000001.0;        // store a double there

    cout << "double ";
    cout << "value = " << *Pd << ": location = " << Pd << endl;
    cout << "location of pointer pd: " << &Pd << endl;
    cout << "size of pt = " << sizeof(Pt);
    cout << ": size of *pt = " << sizeof(*Pt) << endl;
    cout << "size of pd =  " << sizeof(Pd);
    cout << ": size of *pd = " << sizeof(*Pd) << endl;

    return 0;
}
