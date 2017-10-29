template <typename Type>
class Array {
public:
	Array() {
		/* ... */
	}
	Array(int i) {
		Array();
		/* ... */
	}
	Type operator[](int index) {
		return Type();
	}
	double operator()() {
		return 0.0;
	}
	/* ... */
};

template <typename Type>
Type min(const Array<Type>&, int);

template <typename Type>
Type min(const Type*, int);

template <typename Type>
Type min(Type, Type);

#include <cmath>

int main() {
	Array<int> iA(1024);
	int ia[1024];

	// Type == int; min(const Array<int>&, int)
	int ival0 = min(iA, 1024);

	// Type == int; min(const int*, int)
	int ival1 = min(ia, 1024);

	// Type == double; min(double, double)
	double dval0 = min(std::sqrt(iA[0]), std::sqrt(ia[0]));

	return 0;
}
