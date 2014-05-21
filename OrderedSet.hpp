// HW9/10: Ordered Set Class Template
// Peter Hurford and Bryan Fowler

using namespace std;

template <typename T>
int OrderedSet<T>::insert(T x) {
	// pre: x is a pointer, has an id and is capable of being sorted by relational operators.
	// post: inserts x into the ordered set in the proper location determined by the order of the set.
	//       If x is already in the set, it will be repositioned into its proper location, rather than duplicated.

	if (L.length() == maxsize_) { return 0; }		// Enforce maxsize

	T curr;
	L.resetForward();
	for (int i =0; i <L.length(); i++) {			// Traverse the set...
		curr = L.next();
		if( x->id() == curr->id() ) { L.pop(i); }	// if id's match (duplicate detected), remove the duplicate from the list
	}

	int j = 0;										// Keep track of position in the list to determine where to insert x.
	if (L.length() >= 0) {							// If the set is not empty...
		L.resetForward();
		for (int k = 0; k<L.length(); k++) {		// ...traverse the set...
			curr = L.next();
			if (*x >= *curr) { j++; }				// ...if x is larger or equal to the current element traversed, keep looking to place x later.
		}
	L.insert(j, x);									// Use the doubly linked list insert method to insert x in the desired position, keeping the set in order.
	}
	return 1;
}


template <typename T>
T OrderedSet<T>::removeFirst() {
	// pre: set cannot be empty.
	// post: removes and returns the first element in the ordered set.
	// Exception: throw 1 if precondition not met.
	
	if (L.length() == 0) { throw 1; }
	
	T firstItem = L.pop(0);				// Use doubly linked list's pop method to get and delete the first item.
	return firstItem;					// Return the first item.
}


template <typename T>
int OrderedSet<T>::remove(int id) {
	// pre: Set cannot be empty.
	// post: removes the element with the given id from the ordered set.

	for (int i = 0; i<L.length(); i++) {	// Traverse the list...
		if (L[i]->id() == id) {				// ...if the id matches (x is found)...
			L.pop(i);						// ...use doubly linked list's pop method to remove it.
			return 1;						// ...return a 1 to indicate success.
		}
	}
	return 0;								// If we get through the list without returning anything, x was not found.  Return 0 for failure.
}


template <typename T>
int OrderedSet<T>::len() const {
	// post: Returns the length of the ordered set.
	return L.length();		// Return length of doubly linked list where ordered set is stored.
}

template <typename T>
string OrderedSet<T>::str() {
	// str method
	//post: returns a string representation of the OrderedSet formatted as a python list with a star following the item on TOS
	// Note: cannot use L.str() because L.str() does not put a star on TOS
	// Note: did not want to traverse list with ->next because that would require additional friend classing.
	
	stringstream os;
	os << "[";									// Add first bracket
	for (int i = 0; i<L.length(); i++) {		// Traverse the list...
		os << L[i];								// ...add the item
		if (i == 0) { os << "*"; }				// ...if it's the first element (TOS), add a star afterwards
		if (i != L.length()-1) { os << ", "; }	// ...if it's not the last element, add a comma to separate elements
	}
	os << "]";									// Add ending bracket

	return os.str();							// return the string
}
