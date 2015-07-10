#ifndef UTIL_LIST_INCLUDE_
#define UTIL_LIST_INCLUDE_

#include <iostream>

class ilist_item {
public:
    ilist_item(int value, ilist_item *item_to_link_to = 0);
    int value() { return _value; }
    ilist_item *next() { return _next; }
    void next(ilist_item *link) { _next = link; }
    void value(int new_value) { _value = new_value; }

private:
    int _value;
    ilist_item *_next;
};

class ilist {
public:
    // default ctor
    ilist() : _size(0), _at_front(0), _at_end(0) {}
    // copy ctor
    ilist(const ilist&);
    // assignment
    ilist& operator=(const ilist&);


    int size();
    ilist_item *find(int value);

    void insert_front(int value);
    void insert_end(int value);
    void insert(ilist_item *ptr, int value);

    int remove(int value);
    void remove_all();
    void remove_front();

    void concat(const ilist &list);
    void reverse();

    ilist_item *front() { return _at_front; }
    void display(std::ostream &os = std::cout);

    ilist_item* init_iter(ilist_item *it = 0);
    ilist_item* next_iter();

private:
    void insert_all(const ilist &rhs);
    void bump_up_size();
    void bump_down_size();

    int _size;
    ilist_item *_at_front;
    ilist_item *_at_end;
    ilist_item *_current;
};

inline ilist_item::ilist_item(int value, ilist_item *item_to_link_to)
        : _value(value) {
    if (!item_to_link_to)
        _next = 0;
    else {
        _next = item_to_link_to->_next;
        item_to_link_to->_next = this;
    }
}

inline ilist::ilist(const ilist &rhs) : _at_front(0), _at_end(0) {
    insert_all(rhs);
}

inline ilist& ilist::operator=(const ilist &rhs) {
    if (this != &rhs) {
        remove_all();
        insert_all(rhs);
    }
    return *this;
}

inline int ilist::size() { return _size; }

inline void ilist::insert(ilist_item *ptr, int value) {
    if (!ptr)
        insert_front(value);
    else {
        bump_up_size();
        new ilist_item(value, ptr);
    }
}

inline void ilist::insert_front(int value) {
    ilist_item *ptr = new ilist_item(value);
    if (!_at_front)
        _at_front = _at_end = ptr;
    else {
        ptr->next(_at_front);
        _at_front = ptr;
    }
    bump_up_size();
}

inline void ilist::insert_end(int value) {
    if (!_at_end)
        _at_end = _at_front = new ilist_item(value);
    else
        _at_end = new ilist_item(value, _at_end);
    bump_up_size();
}

inline void ilist::remove_front() {
    if (_at_front) {
        ilist_item *ptr = _at_front;
        _at_front = _at_front->next();
        if (_current == ptr)
            _current = _at_front;
        bump_down_size();
        delete ptr;
    }
}

inline ilist_item* ilist::init_iter(ilist_item *it) {
    return _current = it ? it : _at_front;
}

inline ilist_item* ilist::next_iter() {
    ilist_item *next = _current 
        ? _current = _current->next()
        : _current;
    return next;
}

inline void ilist::bump_up_size() { ++_size; }

inline void ilist::bump_down_size() { --_size; }

#endif // UTIL_LIST_INCLUDE_
