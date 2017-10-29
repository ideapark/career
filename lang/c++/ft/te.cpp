#include <string>
#include <vector>
#include <iostream>

template <class T>
T Min(T a, T b) {
	return a < b ? a : b;
}

template <class T>
void swap(std::vector<T> &array, int i, int j) {
	T tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

template <class T>
void sort(std::vector<T> &array, int low, int high) {
	if (low < high) {
		int lo = low;
		int hi = high + 1;
		T elem = array[lo];
		for (;;) {
			while (Min(array[++lo], elem) != elem && lo < high)
				NULL;
			while (Min(array[--hi], elem) == elem && hi > low)
				NULL;
			if (lo < hi)
				swap(array, lo, hi);
			else
				break;
		}
		swap(array, low, hi);
		swap(array, low, hi-1);
		swap(array, hi+1, high);
	}
}

template <class T>
void display(std::vector<T> &array) {
	// display format: <0 1 2 3 4 5 >
	std::cout << "< ";
	for (int ix = 0; ix < array.size(); ++ix)
		std::cout << array[ix] << " ";
	std::cout << ">\n";
}

double da[10] = {
	26.7, 5.7, 37.7, 1.7,
	61.7, 11.7, 59.7, 15.7,
	48.7, 19.7,
};
int ia[16] = {
	503, 87, 512, 61,
	908, 170, 897, 275,
	653, 426, 154, 509,
	612, 677, 765, 703,
};
std::string sa[11] = {
	"a", "heavy", "snow", "was",
	"falling", "when", "they", "left",
	"the", "police", "station",
};

int main() {
	std::vector<double> arrd(da, da+sizeof(da)/sizeof(da[0]));
	std::vector<int> arri(ia, ia+sizeof(ia)/sizeof(ia[0]));
	std::vector<std::string> arrs(sa, sa+sizeof(sa)/sizeof(sa[0]));

	std::cout << "sort array of doubles (size == "
		  << arrd.size() << ")" << std::endl;
	sort(arrd, 0, arrd.size()-1);
	display(arrd);

	std::cout << "sort array of ints (size == "
		  << arri.size() << ")" << std::endl;
	sort(arri, 0, arri.size()-1);
	display(arri);

	std::cout << "sort array of strings (size == "
		  << arrs.size() << ")" << std::endl;
	sort(arrs, 0, arrs.size()-1);
	display(arrs);

	return 0;
}
