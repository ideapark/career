#include <iostream>
#include "list.h"

int main() {
	ilist mylist;
	for (int ix = 0; ix < 10; ix++)
		mylist.insert_front(ix);
	mylist.display();

	std::cout << "\n" << "reverse the list\n";
	mylist.reverse();
	mylist.display();

	ilist mylist_too;
	mylist_too.insert_end(0);
	mylist_too.insert_end(1);
	mylist_too.insert_end(1);
	mylist_too.insert_end(2);
	mylist_too.insert_end(3);
	mylist_too.insert_end(5);
	std::cout << "\n" << "mylist_too:\n";
	mylist_too.display();
	mylist.concat(mylist_too);
	std::cout << "\n" << "mylist after concat with mylist_too:\n";
	mylist.display();

	return 0;
}
