// write.cpp -- using cout.write()

#include <iostream>
#include <cstring>

int main(void)
{
    using std::cout;
    using std::endl;
    const char *state = "Kansas";
    int len = std::strlen(state);
    cout << "Increasing loop index:\n";
    for (int i = 1; i <= len; i++) {
        cout.write(state, i);
        cout << endl;
    }
    // concatenate output
    cout << "Decreasing loop index:\n";
    for (int i = len; i > 0; i--)
        cout.write(state, i) << endl;
    // exceed string length
    cout << "Exceeding string length:\n";
    cout.write(state, len+5) << endl;
    return 0;
}
