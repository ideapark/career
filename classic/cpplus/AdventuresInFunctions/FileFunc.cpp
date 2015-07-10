// FileFunc.cpp

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void FileIt(ostream &OS, double FO, const double FE[], int N);

const int LIMIT = 5;

int main(void)
{
    ofstream FOut;
    const char *FN = "ep-data.txt";
    FOut.open(FN);
    if (!FOut.is_open()) {
        cout << "Can't open " << FN << ". Bye.\n";
        exit(EXIT_FAILURE);
    }
    double Objective;
    cout << "Enter the focal length of your "
        << "telescope objective in mm: ";
    cin >> Objective;
    double EPS[LIMIT];
    cout << "Enter the focal lengths, in mm, of " << LIMIT
        << " eyepieces.\n";
    for (int I = 0; I < LIMIT; I++) {
        cout << "Eyepiece #" << I+1 << ": ";
        cin >> EPS[I];
    }
    FileIt(FOut, Objective, EPS, LIMIT);
    FileIt(FOut, Objective, EPS, LIMIT);
    cout << "Done\n";
    return 0;
}

void FileIt(ostream &OS, double FO, const double FE[], int N)
{
    ios_base::fmtflags Initial;
    Initial = OS.setf(ios_base::fixed); // save initial formatting state
    OS.precision(0);
    OS << "Focal length of objective: " << FO << " mm\n";
    OS.setf(ios::showpoint);
    OS.precision(1);
    OS.width(12);
    OS << "f.1. eyepiece";
    OS.width(15);
    OS << "magnification" << endl;
    for (int I = 0; I < N; I++) {
        OS.width(12);
        OS << FE[I];
        OS.width(15);
        OS << int(FO/FE[I]+0.5) << endl;
    }
    OS.setf(Initial); // restore initial formatting state
}
