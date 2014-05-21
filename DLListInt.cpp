// HW9/10: DLList Class for Integers
// Peter Hurford and Bryan Fowler

#include "DLListInt.h"
#include <string>
#include <sstream>

using namespace std;

DLListInt::DLListInt(const DLListInt& from) {
	// Copy Constructor
	// pre: from is of DLList class.
	// post: Uses the allocCopy method to implement the copy.
	allocCopy(from);
}


DLListInt::~DLListInt() {
	// Destructor
	// post: Uses the dealloc method to deallocate all the dynamically allocated nodes.
	dealloc();
}


DLListInt& DLListInt::operator=(const DLListInt& from) {
	// Assignment Overload
	// pre: from is of DLList class.
	// post: Assigns one DLListInt the values of another DLListInt without memory leaks or other undesired behavior.

	if (this != &from) {		// Prevent self-assignment
		dealloc();				// Delete all dynamic elements
		allocCopy(from);		// Re-create all dynamic elements as a copy
	}
	return *this;				// Return a pointer to itself
}


void DLListInt::append(const int& item) {
	// Append method
	// pre: item is an integer
	// post: places item at the end of the list
	
	IntNode * node = new IntNode(item);						// ...make a new node with no next or prev
	
	if(head == NULL) {										// If the list is empty...	
		head = tail = node;									// ...set the head to that node
	}
	else {													// Otherwise, if the list is not empty...
		node->prev_ = tail;									// ...set the previous node to tail.
		tail->next_ = node;									// ...set the next node of tail to the new node.
		tail = node;										// Set the tail to the new node.
	}
	size++;													// Increment the size by 1.
}


void DLListInt::insert(int index, const int& item) {
	// Insert method
	// pre: Index must be less than or equal to the size of the pre-existing list; item must be an int.
	// post: Places the item in the place of the list defined by the index.
	// Exceptions: Throws IndexError if size is out of bounds.
	
	if(index > size || index < 0) {
		IndexError e; 
		throw e;													// If the index is out of bounds, throw an IndexError.
	}				
	else if(index == size) { append(item); }						// If the index is the size of the list, it's just an append.
	else if(index == 0) {											// Otherwise, if the index is 0... (insert at beginning)
		IntNode * node = new IntNode(item, head, NULL);				// ...Define a new note with a next of what node is in the head and no previous node.
		head->prev_ = node;											// ...Set the node currently at the head to link back to our new node.
		head = node;												// ...Set head to become the new node.
		size++;														// Increment size by one.
	}
	else {															// Otherwise, if the index is not 0...
		IntNode * prevNode = _find(index-1);						// ...Get the prevNode (node before the new node) by using the find method
		IntNode * nextNode = prevNode->next_;						// ...Get the nextNode (node after the new node) by looking at what is currently after prevNode 
		IntNode * node = new IntNode(item, nextNode, prevNode);		// ...Create a new node with the right next and previous nodes
		prevNode->next_ = node;										// ...Insert the new node between the prevNode and nextNode
		nextNode->prev_ = node;
		size++;														// Increment size by one.
	}

		
}


int DLListInt::pop(int index) {
	// pop method
	//pre: Index is less than size and greater than or equal to -1 and the list must be non-empty
	//post: deletes and returns the item at position index using the _delete method
	//Exception: Throws an IndexError if the index is not valid
	
	if(index > size || index < -1 || size == 0) {
		IndexError e;
		throw e;													// If the index is out of bounds, throw an IndexError.
	}
	if(index == -1) { index = size; }								// If index is valid
	return _delete(index);											// ... use the delete method 
}


int& DLListInt::operator[](int index) {
	// Indexing method (bracket overload)
	// pre: Index is an integer and in range (less than or equal to the size of the pre-existing list)
	// post: Uses the find_ method to return the value of the node at position index
	// Exception: Throws IndexError if index is out of range

	if(index > size || index < 0) { 
		IndexError e;
		throw e; 											// If the index is out of bounds, throw an IndexError.
	}
	
	IntNode *node = _find(index);							// Use the _find method to get the node we're looking for.
	return node->item_;										// Return it's item value.
}


string DLListInt::str() const {
	// str method
	//post: returns a string representation of the DLList formatted as a python list
	
	IntNode * curr = head;
	stringstream os;										// creates a stringstream 
	os << "[";												// ...adds the [ symbol to the beginning of the stream
	if(curr){												// ... if the list is non-empty
		os << curr->item_;									// ... add the first element to the string
		curr = curr->next_;		
		while(curr){os << ", " << curr->item_;curr = curr->next_;}	// ... and continue to add elements until the end of the list has been reached
	}
	os << "]";												// add the ] symbol to the end of the string
	return os.str();										// return the string
}


int DLListInt::next() {
// Next method
// post: Returns the next item of the list and advances the iterator.  Throws the StopIteraton if the end of the list is reached.

	if (nextiter) {							// If nextiter already exists...
		nextiter = nextiter->next_;			// ...advance to the next node and
		if (!nextiter) {					// ...if nextiter no longer exists (no next node)...
			StopIteration stop;				// ...stop the iteration.
			throw stop;	
		}
	}
	else { nextiter = head; }				// Otherwise, if nextiter doesn't already exist, start at the head.
	return nextiter->item_;						// Return the item.
}


void DLListInt::allocCopy(const DLListInt& from) {
	//allocCopy method
	//post: allocates new storage for a DLListInt object and copies "from" into that storage
	
	IntNode *snode, *node; 									// Declare variables
	
	snode = from.head;										// start snode at the head of the source list
	if(snode){												// ... if the source list is non-empty
		node = head = new IntNode(snode->item_);			// ... allocate storage for a new node and assign the head to that node
		snode = snode->next_;								// ... move snode to the next node in the source
	}
	else{head = NULL;}										// if the source list is empty, set the new list's head to NULL
	while(snode){											// traverse list
		node->next_ = new IntNode(snode->item_,NULL,node);	// ... allocating new storage for each next node and assign the next of the current node to that node
		node = node->next_;									
		snode = snode->next_;								// ... get the next node from source
	}
	size = from.size;										// copy size
	tail = node;											// set tail to the last node
	nextiter = NULL;										// reset the copy of the iterator
}


void DLListInt::dealloc() {
	// Deallocate method
	// post: Deletes all dynamically allocated nodes

	IntNode *node = head;		// Start at the head
	IntNode *tmp_node;			// Define a temporary node

	while (node) {				// While a node still exists...
		tmp_node = node;		// ...Store the current node
		node = node->next_;		// ...Go to the next node
		delete tmp_node;		// ...Delete the current node
	}
}


IntNode * DLListInt::_find(int index) {
	// Find method
	// pre: Index is an integer and in range.
	// post: returns the node at position index.
	// Exception: Throws IndexError if index is out of range.

	if(index > size || index < 0) { 
		IndexError e;
		throw e; }											// If the index is out of bounds, throw an IndexError.

	IntNode * node = head;									// Start at the head
	for (int i=0; i<index; i++) {							// Until we reach the desired node...
		node = node->next_;									// ...look to the next node.
	}

	return node;											// Return the desired node.
}


int DLListInt::_delete(int index) {
	//delete method
	//pre: index is an integer and in range
	//post: deletes and returns the node at position index
	//Exception: Throws IndexError if index is out of range
	
	int retVal;
	if (size == 1) {			// if list is size one...
		retVal = head->item_;   // ...get the item to return
		head = tail = NULL;     // ...set head and tail to null
	}
	else if (index == 0) {		// ...Otherwise, if index is 0 (delete at beginning)...
		retVal = head->item_;	// ...get the item to return
		head = head->next_;		// ...set the next
		head->prev_ = NULL;		// ...set the prev
	}
	else if (index == size) {	// ...Otherwise, if index is size (delete at end)...
		retVal = tail->item_;	// ...get the item to return
		tail = tail->prev_;		// ...set the prev
		tail->next_ = NULL;		// ...set the next
	}
	else {											// ...Otherwise (delete at middle)...
		IntNode * prevNode, * Node, * nextNode;		// ...initialize variables
		prevNode = _find(index - 1);				// ...get prevNode using _find method
		Node = prevNode->next_;						// ...get Node from prevNode's next
		nextNode = Node->next_;						// ...get nextNode from Node's next
		retVal = Node->item_;						// ...get the item to return
		prevNode->next_ = nextNode;					// ...set the next of prevNode
		nextNode->prev_ = prevNode;					// ...set the prev of nextNode
	}

	size--;						// Decrement the size
	return retVal;				// Return the deleted item
}

ostream& operator<<(std::ostream& os, const DLListInt& l) {
	// Output method (<< Overload)
	// post: allows cout to print the list as desired
	os << l.str();
	return os;
}
