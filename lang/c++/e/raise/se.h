#ifndef STACK_EXCEPTION_H
#define STACK_EXCEPTION_H

class PopOnEmpty { /* ... */ };

class PushOnFull {
public:
PushOnFull(int i) : _value(i) {}
	int value() { return _value; }
private:
	int _value;
};

#endif // STACK_EXCEPTION_H
