#include <vector>

int main(void)
{
    auto x = 0.0; // ok, x is double because 0.0 is double
    double y = 0; // ok, 0 automatically converted to 0.0
    auto z = 0;   // oops, z is int because 0 is int

    std::vector<double> Scores;
    std::vector<double>::iterator PV = Scores.begin();
    auto PVA = Scores.begin(); // the same to the above

    return 0;
}
