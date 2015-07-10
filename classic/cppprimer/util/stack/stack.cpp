#include "stack.h"
#include <iostream>

bool iStack::pop(int &top_value) {
    if (empty())
        return false;
    top_value = _stack[--_top];
    std::cout << "iStack::pop(): " << top_value << std::endl;
    return true;
}

bool iStack::push(int value) {
    std::cout << "iStack::push(" << value << ")\n";
    if (full())
        return false;
    _stack[_top++] = value;
    return true;
}

void iStack::display() {
    if (!size()) {
        std::cout << "(0)\n";
        return;
    }
    std::cout << "(" << size() << ") (bot: ";
    for (int ix = 0; ix < _top; ++ix)
        std::cout << _stack[ix] << " ";
    std::cout << " :top)\n";
}
