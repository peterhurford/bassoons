// HW9/10: Queue Class for DES (Header)
// Peter Hurford and Bryan Fowler

#ifndef QUEUE_H
#define QUEUE_H
#include <string>
#include "DLList.h"
#include <iostream>
#include <cstdlib>

template <typename T>
class Queue;

template <typename T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& q);

template <typename T>
class Queue {
		
	public:
		Queue<T>(int maxsize = 12) { // define constructor
			// pre: maxsize is an int
			// post: A queue maintains a collection of elements in a doubly linked list
			
			maxsize_ = maxsize;
		}
		~Queue<T>() {}				// declare destructor

		int enqueue(T & x);			// declare enqueue method
		T dequeue();				// declare dequeue method
		int len();					// declare accessor for length of queue
		std::string str();			// declare print method

	private:					    // declare variables
		DLList<T> L;
		int maxsize_;
		friend std::ostream& operator<< <T>(std::ostream& os, const Queue& q);
		
};
template <typename T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& q);

#include "Queue.hpp"
#endif
