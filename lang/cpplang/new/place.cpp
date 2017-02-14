#include <iostream>
#include <new>

const int chunk = 16;

class Foo {
public:
    Foo() { _val = 0; }
    int val() { return _val; }
private:
    int _val;
};

// pre-allocated
char *buf = new char[sizeof(Foo)*chunk];

int main() {
    Foo *pb = new (buf) Foo;
    if (pb->val() == 0)
        std::cout << "new expression worked!" << std::endl;
    delete[] buf;

    return 0;
}
