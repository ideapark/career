// Recursion.cpp -- using recursion

#include <iostream>

void CountDown(int N);

int main(void)
{
    CountDown(8); // call the recursive function
    return 0;
}

void CountDown(int N)
{
    using namespace std;
    cout << "Counting down ... " << N << "@" << &N << endl;
    if (N > 0)
        CountDown(N-1);
    cout << N << "@" << &N << ": Kaboom!\n";
}
