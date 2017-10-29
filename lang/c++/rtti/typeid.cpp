#include <iostream>
#include <typeinfo>

class Base { /* NO virtual functoin */ };
class Derived : public Base { /* NO virtual function */ };

class VirtualBase {
public:
	virtual ~VirtualBase() { }
};

class VirtualDerived : public VirtualBase {
public:
	virtual ~VirtualDerived() { }
};

int main(int argc, char *argv[])
{
	int iobj;
	std::cout << typeid(iobj).name() << std::endl;
	std::cout << typeid(8.16).name() << std::endl;

	Derived dobj;
	Base *pb = &dobj;
	std::cout << typeid(*pb).name() << std::endl;

	VirtualDerived vdobj;
	VirtualBase *vpb = &vdobj;
	std::cout << typeid(*vpb).name() << std::endl;

	return 0;
}
