#include <iostream>
#include "list.h"

int main() {
    ilist mylist;
    for (int ix = 0; ix < 10; ix++) {
        mylist.insert_front(ix);
        mylist.insert_end(ix);
    }

    std::cout << "Ok: after insert front() and insert end()\n";
    mylist.display();
    ilist_item *it = mylist.find(8);
    std::cout << "\n"
              << "Searching for the value 8: found it << "
              << (it ? " yes!\n" : " no!\n");

    mylist.insert(it, 1024);
    std::cout << "\n"
              << "Inserting element 1024 following the value 8\n";
    mylist.display();

    int elem_cnt = mylist.remove(8);
    std::cout << "\n"
              << "Removed " << elem_cnt << " of the value 8\n";
    mylist.display();

    std::cout << "\n" << "Removed front element\n";
    mylist.remove_front();
    mylist.display();

    std::cout << "\n" << "Removed all elements\n";
    mylist.remove_all();
    mylist.display();

    return 0;
}
