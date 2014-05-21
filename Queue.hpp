// HW9/10: Template Queue Class
// Peter Hurford and Bryan


#include <iostream>
#include <sstream>
using namespace std;

template <typename T>
int Queue<T>::enqueue(T & x) { // define enqueue method
	// pre: queue size does not exceed max size
	// post: inserts an element x into the queue using the doubly linked list's append method.
	// Return 1 if enqueue is successful and 0 if enqueue failed because of no additional room in the Queue.

	if (L.length() + 1 > maxsize_) { return 0; }		// return 0 for no additional room in the Queue.

	L.append(x);								// Add object to end of queue
	return 1;									// Return 1 to indicate success
}

template <typename T>
T Queue<T>::dequeue() { // define dequeue method
	// pre: queue is not empty.
	// post: removes and returns the element from the queue using the doubly linked list's pop method.
	// An integer value is "thrown" if dequeue() is invoked on an empty Queue. (For now the particular integer value is not important.)

	if (L.length() == 0) { throw 42; } 		// throw integer for empty Queue.

	T r = L.pop(0); 						// Get first element in the queue

	return r;								// return removed element
}

template <typename T>
int Queue<T>::len() { // define accessor for length of queue
	return L.length();
}					

template <typename T>
string Queue<T>::str() {
	// str method
	// post: returns a string representation of the Queue formatted as a python list with a star following the item on TOS
	// Note: cannot use L.str() because L.str() does not put a star on TOS
	// Note: did not want to traverse list with ->next because that would require additional friend classing.
	
	stringstream os;
	os << "[";									// Add first bracket
	L.resetForward();
	T curr;										
	for (int i = 0; i<L.length(); i++) {		// Traverse the list...
		curr = L.next();
		os << curr;								// ...add the item
		if (i == 0) { os << "*"; }				// ...if it's the first element (TOS), add a star afterwards
		if (i != L.length()-1) { os << ", "; }	// ...if it's not the last element, add a comma to separate elements
	}
	os << "]";									// Add ending bracket

	return os.str();							// return the string
}


template <typename T>
ostream& operator<< (std::ostream& os, const Queue<T>& q) {
	// Output method (<< Overload)
	// post: allows cout to print the list as desired
	os << q.str();
	return os;
}
