// stringfile.cpp -- read strings from a file

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(void)
{
    using namespace std;
    ifstream fin;
    fin.open("tobuy.txt");
    if (fin.is_open() == false) {
        cerr << "Can't open file. Bye.\n";
        exit(EXIT_FAILURE);
    }
    string item;
    int count = 0;
    while (getline(fin, item, ':')) {
        ++count;
        cout << count << ": " << item << endl;
    }
    cout << "Done\n";
    fin.close();
    return 0;
}
