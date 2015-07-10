#include <iostream>
#include <iomanip>

const int max = 65000;
const int lineLength = 5;

void fibonacci(int max) {
    if (max < 2)
        return;
    std::cout << "     0     1";
    int v1 = 0, v2 = 1, cur;
    for (int ix = 3; ix <= max; ++ix) {
        cur = v1 + v2;
        if (cur > ::max)
            break;
        std::cout << std::setw(6) << cur;
        v1 = v2;
        v2 = cur;
        if (ix % lineLength == 0)
            std::cout << std::endl;
    }
}

int main() {
    std::cout << "Fibonacci Series: 32\n";
    fibonacci(32);
    return 0;
}
