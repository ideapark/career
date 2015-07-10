#include <cassert>
#include "garray.h"

template <class elemType>
explicit Array::Array(int size) {
	_size = size;
	ia = new elemType[_size];
	std::assert(ia != NULL);
}

template <class elemType>
Array::Array(elemType *array, int array_size) {
	_size = array_size;
	ia = new elemType[_size];
	std::assert(ia != NULL);
	for (int i = 0; i < _size; i++)
		ia[i] = array[i];
}

template <class elemType>
Array::Array(const Array &rhs) {
	_size = rhs.size();
	ia = new elemType[_size];
	std::assert(ia != NULL);
	for (int i = 0; i < _size; i++)
		ia[i] = rhs.ia[i];
}

template <class elemType>
bool Array::operator==(const Array &rhs) const {
	if (_size != rhs.size())
		return false;
	for (int i = 0; i < rhs.size(); i++)
		if (ia[i] != rhs.ia[i])
			return false;
	return true;
}

template <class elemType>
bool Array::operator!=(const Array &rhs) const {
	return !(this == rhs);
}

template <class elemType>
Array& Array::operator=(const Array &rhs) {
	_size = 0;
	delete[] ia;
	_size = rhs.size();
	ia = new elemType[_size];
	std::assert(ia != NULL);
	for (int i = 0; i < _size; i++)
		ia[i] = rhs.ia[i];
	return *this;
}
