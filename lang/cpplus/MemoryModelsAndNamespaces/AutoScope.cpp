// AutoScope.cpp -- illustrating scope of automatic variables

#include <iostream>

void Oil(int X);

int main(void)
{
    using namespace std;
    int Texas = 31;
    int Year = 2011;
    cout << "In main(), texas = " << Texas << ", &texas = ";
    cout << &Texas << endl;
    cout << "In main(), year = " << Year << ", &year = ";
    cout << &Year << endl;
    Oil(Texas);
    cout << "In main(), texas = " << Texas << ", &texas = ";
    cout << &Texas << endl;
    cout << "In main(), year = " << Year << ", &year = ";
    cout << &Year << endl;
    return 0;
}

void Oil(int X)
{
    using namespace std;
    int Texas = 5;
    cout << "In oil(), texas = " << Texas << ", &texas = ";
    cout << &Texas << endl;
    cout << "In oil(), x = " << X << ", &x = ";
    cout << &X << endl;
    {                     // start a block
        int Texas = 113;
        cout << "In block, texas = " << Texas;
        cout << ", &texas = " << &Texas << endl;
        cout << "In block, x = " << X << ", &X = ";
        cout << &X << endl;
    }                     // end a block
    cout << "Post-block texas = " << Texas;
    cout << ", &texas = " << &Texas << endl;
}
