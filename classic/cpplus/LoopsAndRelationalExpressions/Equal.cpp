// Equal.cpp -- equality vs assignment

#include <iostream>

int main(void)
{
    using namespace std;

    int QuizScores[10] = {
        20, 20, 20, 20, 20,
        19, 20, 18, 20, 20
    };
    cout << "Doing it right:\n";
    int I;
    for (I = 0; QuizScores[I] == 20; I++)
        cout << "quiz " << I << " is a 20\n";
    // Warning: you may prefer reading about this program
    // to actually running it.
    cout << "Doing it dangerously wrong:\n";
    for (I = 0; QuizScores[I] = 20; I++)
        cout << "quiz " << I << " is a 20\n";

    return 0;
}
