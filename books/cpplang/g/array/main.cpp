#include <iostream>
#include "garray.h"

int main(int argc, char *argv[]) {
	const int array_size = 4;
	Array<int> ia(array_size);
	Array<double> da(array_size);
	Array<char> ca(array_size);

	for (int ix = 0; ix < array_size; ix++)
		std::cout << "[" << ix << "] ia: " << ia[ix]
			<< "\tca: " << ca[ix]
			<< "\tda: " << da[ix] << std::endl;
	return 0;
}
