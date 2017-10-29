#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdlib>

template <typename Type> class Queue;

template <typename Type>
class QueueItem {
	friend class Queue<Type>;
	friend std::ostream& operator<<(std::ostream &os, const QueueItem<Type> &qi);
private:
QueueItem(const Type val) : item(val) { }

	Type      item;
	QueueItem *next;
};

template <typename Type>
class Queue {
	friend std::ostream& operator<<(std::ostream &os, const Queue<Type> &q);
public:
Queue() : front(0), back(0) { }
	~Queue();

	Type remove();
	void add(const Type &val);
	bool is_empty() const {
		return front == 0;
	}
private:
	QueueItem<Type> *front;
	QueueItem<Type> *back;
};

template <class Type>
std::ostream& operator<<(std::ostream &os, const QueueItem<Type> &qi) {
	os << qi.item;
	return os;
}

template <class Type>
std::ostream& operator<<(std::ostream &os, const Queue<Type> &q) {
	os << "< ";
	QueueItem<Type> *p;
	for (p = q.front; p; p = p->next)
		os << *p << " ";
	os << " >";
	return os;
}

template <typename Type>
Queue<Type>::~Queue() {
	while (!is_empty())
		remove();
}

template <typename Type>
void Queue<Type>::add(const Type &val) {
	QueueItem<Type> *pt = new QueueItem<Type>(val);
	pt->next = 0;
	if (is_empty())
		front = back = pt;
	else {
		back->next = pt;
		back = pt;
	}
}

template <typename Type>
Type Queue<Type>::remove() {
	if (is_empty()) {
		std::cerr << "remove() on empty queue\n";
		std::exit(-1);
	}
	QueueItem<Type> *pt = front;
	front = front->next;
	Type retval = pt->item;
	delete pt;
	return retval;
}

#endif // QUEUE_H
