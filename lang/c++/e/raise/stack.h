#ifndef STACK_H
#define STACK_H

#include <vector>
#include "se.h"

class iStack {
public:
iStack(int capacity) : top(0), stack(capacity) {}
	void pop(int &top_value) throw(PopOnEmpty);
	void push(int value) throw(PushOnFull);
	bool full();
	bool empty();
	void display();
	int size();

private:
	unsigned int top;
	std::vector<int> stack;
};

inline bool iStack::full() {
	return top >= stack.size();
}

inline bool iStack::empty() {
	return top == 0;
}

inline int iStack::size() {
	return top;
}

#endif // STACK_H
