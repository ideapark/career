// Lotto.cpp -- probability of winning

#include <iostream>

// Note: some implementations require double instead of long double
long double Probability(unsigned Numbers, unsigned Picks);

int main(void)
{
    using namespace std;
    double Total, Choices;
    cout << "Enter the total number of choices on the game card and\n"
            "the number of picks allowed:\n";
    while ((cin >> Total >> Choices) && Choices <= Total) {
        cout << "You have one chance in ";
        cout << Probability(Total, Choices); // compute the odds
        cout << " of winning.\n";
        cout << "Next two numbers (q to quit): ";
    }
    cout << "bye\n";
    return 0;
}

// the following function calculate the probability of picking picks
// number correctly from numbers choices
long double Probability(unsigned Numbers, unsigned Picks)
{
    long double Result = 1.0; // here come some local variable
    long double N;
    unsigned P;
    for (N = Numbers, P = Picks; P > 0; N--, P--)
        Result = Result * (N / P);
    return Result;
}
