// TwoSwap.cpp -- specialization overrides a template

#include <iostream>

template <typename T>
void Swap(T &A, T &B);

struct Job {
    char Name[40];
    double Salary;
    int Floor;
};

// explicit specialization
template <> void Swap<Job>(Job &J1, Job &J2);
void Show(const Job &j);

int main(void)
{
    using namespace std;
    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);
    int I = 10, J = 20;
    cout << "i, j = " << I << ", " << J << ".\n";
    cout << "Using compiler-generated int swapper:\n";
    Swap(I, J); // generates void Swap(int &, int &)
    cout << "Now i, j = " << I << ", " << J << ".\n";

    Job Sue = { "Susan Yaffe", 73000.60, 7 };
    Job Sidney = { "Sidney Taffee", 78060.72, 9 };
    cout << "Before job swapping:\n";
    Show(Sue);
    Show(Sidney);
    Swap(Sue, Sidney); // uses void Swap(Job &, Job &)
    cout << "After job swapping:\n";
    Show(Sue);
    Show(Sidney);

    return 0;
}

    template <typename T>
void Swap(T &A, T &B) // general version
{
    T Temp;
    Temp = A;
    A = B;
    B = Temp;
}

// swaps just the salary and floor fields of a job structure
template <> void Swap<Job>(Job &J1, Job &J2) // specialization
{
    double T1;
    int T2;
    T1= J1.Salary;
    J1.Salary = J2.Salary;
    J2.Salary = T1;
    T2 = J1.Floor;
    J1.Floor = J2.Floor;
    J2.Floor = T2;
}

void Show(const Job &J)
{
    using namespace std;
    cout << J.Name << ": $" << J.Salary
        << " on floor " << J.Floor << endl;
}
