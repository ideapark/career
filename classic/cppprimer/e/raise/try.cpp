#include <iostream>
#include "stack.h"
#include "se.h"

int main() {
    iStack stack(16);
    stack.display();

    try {
        for (int ix = 1; ix < 128; ++ix) {
            if (ix % 3 == 0)
                stack.push(ix);
            if (ix % 4 == 0)
                stack.display();
            if (ix % 10 == 0) {
                int dummy;
                stack.pop(dummy);
                stack.display();
            }
        }
    } catch (PushOnFull &e) {
        std::cerr << "trying to push a value " 
            << e.value() 
            << " on a full stack\n";
    } catch (PopOnEmpty) {
        std::cerr << "trying to pop a value on an empty stack\n";
    } catch (...) {
        std::cerr << "unknown exception caught\n";
    }

    return 0;
}
