// HW 9/10: OrderedSet Header
// Peter Hurford and Bryan Fowler

#ifndef _ORDEREDSET_H
#define _ORDEREDSET_H
#include <string>
#include "Event.h"
#include "DLList.h"


template <typename T>
class OrderedSet {
	friend std::ostream& operator<<(std::ostream& os, const OrderedSet& s) { os << s.str(); return os; }
public:
	OrderedSet(int maxsize = 8) { maxsize_ = maxsize; }
	~OrderedSet() {}
	int insert(T x);
	T removeFirst();
	int remove(int id);
	int len() const;
	std::string str();
private:
	DLList<T> L;
	int maxsize_;
};

#include "OrderedSet.hpp"
#endif
		
