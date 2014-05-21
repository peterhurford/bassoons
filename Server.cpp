// HW10: Server Class
// Peter Hurford and Bryan Fowler

#include "Server.h"
#include <ostream>

using namespace std;

bool Server::available() {
	//  This method simply returns a boolean indicating whether or not the Server object is busy servicing a customer.
	return !busy;
}


void Server::startService(Customer & c) {
	/* 	This method is invoked either because of a customer arrival, or, internally, based on
		completion of some previous servicing of a customer. It is responsible for setting variables
		used in the gathering of statistics of the simulation (for instance, this point in time marks
		the end of the waiting time for a customer, and begins the service time for that customer),
		as well is internally recording the customer being serviced and that the server is now busy.
		Finally, it should determine the customer service completion time, and insert itself back into
		the simulator to execute() at that time. The next event time should be the current time plus an
		service time given by an exponential distribution with mean mean. 								*/

		current = c;									// Record customer being serviced
		busy = true;									// Record that server is now busy

		double random_ = exp(gen); 						// Define the interval to add
		double nextTime = sim_->now() + random_;		// Determine end service time time for this customer using random number distribution
		time_ = nextTime;								// Set its time to next time
		sim_->insert(this);								// Reinsert it back into the OrderedSet

		totalServiceTime += random_;					// Record stats for total service time
}


void Server::execute() {
	/*	This method is invoked (by the Simulator doAllEvents()) to mark the
		completion of service for the "current" customer. On service completion, the Server
		should record/update any statistics for the simulation, and should mark itself as
		now available. If the queue has any waiting customers, it should dequeue the first
		customer and invoke its own startService() method.										*/

	services++;							// Increment number of services

	// Check to see whether current customer has to start over (feedback)
	double r = rand() % 1000;						// Generate a random number between 0 and 1 <cplusplus.com/reference/cstdlib/rand>
	if (r <= failureMean_ * 1000) {					// chance of having to start over (user defined)
		failures++;									// Increment failures by one
		current.fail();
		if (current.getfails() <= tolerance_) {		// Trash all customers who fail more than twice
			Q->enqueue(current);					// Insert the Customer Arrival into the simulator (ordered set of events)
		}
		else { trash(); }
	}
	
	
	// Start next customer or declare available
	if (Q->len() > 0) {				// If queue is not empty...
		Customer c;
		c = Q->dequeue();			// ...remove first element from the queue as next available customer and...

		// Record stats for total time spent waiting in queue
		double enTime = c.time();
		double WaitTime = sim_->now() - enTime;
		totalWaitTime += WaitTime;

		startService(c);			// ...start service for that customer
	}
	else {							// If queue is empty...
		busy = false;				// ...set server to be available
	}	
}
