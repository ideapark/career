#include "strutil.h"
#include <cstring>

bool String::operator==(const String &rhs) {
	if (_size != rhs._size)
		return false;
	return std::strcmp(_string, rhs._string) ? false: true;
}
