#include <string>
#include <iostream>
#include <cstddef>

int main() {
    size_t ia;
    ia = sizeof(ia);
    ia = sizeof ia;

    ia = sizeof(int);
    int *pi = new int[12];
    std::cout << "pi  : " << sizeof(pi) << std::endl
              << "*pi : " << sizeof(*pi) << std::endl;

    std::string st1("foobar");
    std::string st2("a mighty oak");
    std::string *ps = &st1;
    std::cout << "st1 : " << sizeof(st1) << std::endl
              << "st2 : " << sizeof(st2) << std::endl
              << "ps  : " << sizeof(ps) << std::endl
              << "*ps : " << sizeof(*ps) << std::endl;

    std::cout << "short    : " << sizeof(short) << std::endl;
    std::cout << "short*   : " << sizeof(short*) << std::endl;
    std::cout << "short&   : " << sizeof(short&) << std::endl;
    std::cout << "short[3] : " << sizeof(short[3]) << std::endl;
    return 0;
}
