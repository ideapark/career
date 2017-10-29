#ifndef UTIL_STACK_INCLUDE_
#define UTIL_STACK_INCLUDE_

#include <vector>
#include <iostream>

class iStack {
public:
iStack(int capacity) : _stack(capacity), _top(0) {}

	bool pop(int &value);
	bool push(int value);

	bool full();
	bool empty();

	void display();
	int size();

private:
	int _top;
	std::vector<int> _stack;
};

inline int iStack::size() {
	return _top;
}

inline bool iStack::empty() {
	return _top ? false : true;
}

inline bool iStack::full() {
	return _top < _stack.size()-1 ? false : true;
}

#endif // UTIL_STACK_INCLUDE_
