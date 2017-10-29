#include <iostream>
#include "stack.h"
#include "se.h"

void iStack::pop(int &top_value) throw(PopOnEmpty) {
	if (empty())
		throw PopOnEmpty();
	top_value = stack[--top];
	std::cout << "iStack::pop(): " << top_value << std::endl;
}

void iStack::push(int value) throw(PushOnFull) {
	std::cout << "iStack::push(" << value << ")\n";
	if (full())
		throw PushOnFull(value);
	stack[top++] = value;
}

void iStack::display() {
	std::cout << "(" << top << ") [";
	for (unsigned int ix = 0; ix < stack.size(); ++ix) {
		std::cout << stack[ix] << " ";
	}
	std::cout << "]" << std::endl;
}
