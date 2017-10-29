#include <iostream>
#include "list.h"

int main() {
	ilist mylist;
	for (int ix = 0; ix < 10; ix++) {
		mylist.insert_front(ix);
		mylist.insert_end(ix);
	}
	std::cout << "\n" << "Use of init_iter() and next_iter() "
		  << "to iterate across each list item:\n";
	ilist_item *iter;
	for (iter = mylist.init_iter(); iter; iter = mylist.next_iter())
		std::cout << iter->value() << " ";

	std::cout << "\n" << "Use of copy constructor\n";
	ilist mylist2(mylist);
	mylist.remove_all();
	for (iter = mylist2.init_iter(); iter; iter = mylist2.next_iter())
		std::cout << iter->value() << " ";
	std::cout << "\n";

	return 0;
}
