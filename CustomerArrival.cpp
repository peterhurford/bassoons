// HW10: CustomerArrival Class
// Peter Hurford and Bryan Fowler

#include "CustomerArrival.h"
#include "Customer.h"
#include <sstream>
#include <string>
#include <random>
using namespace std;

string CustomerArrival::str() const {
	// Yield a string of the form "<Arrival id: time>".

	stringstream s;												// initialize string
	s << "<Arrival id: " << id_ << ": " << time_ << ">";		// Print string
	return s.str();												// Return string
}


void CustomerArrival::execute() {
	/*  Customers "arrive" by being created each time this Event runs its execute method. A newly arrived customer
		should generate its own string label, based on the data member keeping track of how many customers have been
		generated. The arrival time for the newly created customer should be the current time of the simulation. The
		execute() method should check the status of the server and, if available, initiate service on the generated
		customer. Otherwise, the customer should be placed in the shared queue.

		The CustomerArrival Event should then determine the next customer arrival time, and insert itself back into
		the simulator to execute at that time.  The next arrival time should be the current time plus an inter arrival
		time given by an exponential distribution with mean mean.												*/

	num_++;											// Increment the count of cutomers generated
	
	stringstream s;									// initalize string
	s << num_;										// create label from number

	Customer c(sim_->now(), s.str());				// Create the customer with current time and specified label

	if (num_ < count_) {							// if there are still more CustomerArrivals...
		double random_ = exp(gen); 					// ...define the interval to add and...
		double nextTime = sim_->now() + random_;	// ...determine arrival time for next customer using random number distribution and...
		time_ = nextTime;							// ...set the time to nextTime...
		sim_->insert(this);							// ...reinsert it back into the OrderedSet and...

		totalArrivalTime += random_;				// ...collect for total arrival time stat.
	}

	if (S1->available() == false && S2->available() == false) {					// If the server is busy...
		Q->enqueue(c);															// ...put the customer on the queue to wait and...
		if (Q->len() > maxQueue) { maxQueue++; }								// ...if the total queue length exceeds the max queue stat, record the new stat.
	}
	else {																		//...otherwise...
		if (S1->available() == true) {
			S1->startService(c);												// ...start server to begin servicing the customer with first server
		}
		else { S2->startService(c); }											// ...if first server is busy, serve with second server
	}
}
