int main(void)
{
    int hamburgers = {24}; // set hamburgers to 24
    int emus{7};      // set emus to 5
    int rheas = {12}; // set rheas to 12
    int rocs = {};    // set rocs to 0
    int psychics{};   // set psychics to 0
    int i = { 10.0 }; // compiler warning: double to int

    const int Code = 66;
    int X = 66;
    char C1{31325}; // narrowing, not allowed
    char C2 = {66}; // allowed because char can hold 66
    char C3{Code};  // ditto
    char C4 = {X};  // not allowed, X is not constant

    X = 31325;
    char C5 = X; // allowed by this form of initialization

    return 0;
}
