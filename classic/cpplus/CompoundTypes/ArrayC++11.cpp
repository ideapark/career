// ArrayC++11.cpp -- C++ array initialization

int main(void)
{
    double Earnings[4] { 1.2e4, 1.6e4, 1.1e4, 1.7e4 }; // okay with C++11
    unsigned int Counts[10] = {}; // all elements set to 0
    float Balances[100] {};       // all elements set to 0
    long Plifs[] = { 25, 92, 3.0 }; // not allowed, list-initialization 
                                    // protects against narrowing
    char Slifs[4] = { 'h', 'i', 1122011, '\0' }; // not allowed
    char Tlifs[4] = { 'h', 'i', 112, '\0' };     // allowed

    return 0;
}
