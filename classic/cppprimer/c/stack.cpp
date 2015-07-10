#include <stack>
#include <iostream>

int main() {
    const int ia_size = 10;
    int ia[ia_size] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

    // fill stack
    int ix = 0;
    std::stack<int> intStack;
    for ( ; ix < ia_size; ++ix)
        intStack.push(ia[ix]);
    int error_cnt = 0;
    if (intStack.size() != ia_size) {
        std::cerr << "oops! invalid intStack size: "
                  << intStack.size()
                  << "\t expected: " << ia_size << std::endl;
        ++error_cnt;
    }
    int value;
    while (intStack.empty() == false) {
        value = intStack.top();
        if (value != --ix) {
            std::cerr << "oops! expected " << ix
                 << " received " << value
                 << std::endl;
        }
        // pop top element
        intStack.pop();
    }
    std::cout << "Our program ran with "
              << error_cnt << " errors!"
              << std::endl;
    return 0;
}
