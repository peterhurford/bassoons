// HW10: Header for the Simulator Class
// Peter Hurford and Bryan Fowler

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "OrderedSet.h"
#include "Event.h"
#include "Queue.h"
#include "Customer.h"

class Server;						// Declare Server for private
class CustomerArrival;				// Declare CustomerArrival for private

class Simulator {
	public:
		Simulator(); 				// Declare Constructor
		
		virtual ~Simulator();		// Declare Destructor
		
		double now() const; 		// Return value of current virtual time
		int insert(Event * e); 		// Given a pointer to an event, insert in Future events list
		void doAllEvents(); 		// Main engine to drive simulation
		void sink();				// Method to dump stats
		int pass_num();				// Declare accessor method that passes total customers created from CustomerArrival
		
		// Setup will change from simulation to simulation. The following is specific to the MM1 Queue simulation.
		virtual void setup(int custCount, double arrivalMean = 10.0, double serviceMean = 5.0, double failureMean = 0.1, int tolerance = 2);
	
	private:
		double vtime_; 					// Current virtual time of the simulation
		OrderedSet<Event*> events; 		// Future events list in time order
		Queue<Customer> * Q;			// Queue
		Server * S1;					// First Server
		Server * S2;					// Second Server
		CustomerArrival * C;			// Customer Arrival
};

# endif
