// And.cpp -- using the logical AND operator

#include <iostream>

const int ARRAY_SIZE = 6;

int main(void)
{
    using namespace std;

    float Naaq[ARRAY_SIZE];
    cout << "Enter the NAAQs (New Age Awareness Quotients) "
         << "of\nyour neighbors. Program terminates "
         << "when you make\n" << ARRAY_SIZE << " entries "
         << "or enter a negative value.\n";
    int I = 0;
    float Temp;
    cout << "First value: ";
    cin >> Temp;
    while (I < ARRAY_SIZE && Temp >= 0) { // 2 quitting criteria
        Naaq[I] = Temp;
        ++I;
        if (I < ARRAY_SIZE) { // room left in the array
            cout << "Next value: ";
            cin >> Temp; // so get next value
        }
    }
    if (I == 0)
        cout << "No data -- bye\n";
    else {
        cout << "Enter your NAAQ: ";
        float You;
        cin >> You;
        int Count = 0;
        for (int J = 0; J < I; J++)
            if (Naaq[J] > You)
                ++Count;
        cout << Count;
        cout << " of your neighbors have greater awareness of\n"
             << "the New Age than you do.\n";
    }
    return 0;
}
