// HW10: Header for the CustomerArrival Class
// Peter Hurford and Bryan Fowler

#include <string>
#include <random>
#include "Event.h"
#include "Queue.h"
#include "Customer.h"
#include "Server.h"
#include "Simulator.h"


class CustomerArrival: public Event {
	public:
		CustomerArrival(double mean = 10.0, Queue<Customer> * queue = NULL, Server * server1 = NULL, Server * server2 = NULL, Simulator * sim = NULL, int count = 10, double time=0.0) : // Define constructor
			/*  The constructor must place customers on Queue shared with the server. If no customers are waiting
				on queue, it must invoke the server to begin servicing a customer, and it needs the Simulator itself
				to add the CustomerArrival Event into the simulator's OrderedSet.  For each of these interacting
				objects, the constructor is given a pointer to the corresponding object, which it will store in private
				data members for the use of its member functions. The constructor is also given a count of how many
				total times to generate a Customer as well as the time for the first arrival.							*/

			exp(1/mean), gen(rd()) {	// Initialize exponential distribution
				
			num_ = 0;
			mean_ = mean;
			Q = queue;
			S1 = server1;
			S2 = server2;
			sim_ = sim;
			count_ = count;
			maxQueue = 0;
			totalArrivalTime = 0.0;
			time_ = time;
			id_ = 0;
		}

		virtual ~CustomerArrival() {};									// Define destructor (empty because no dynamic elements)
		std::string str() const;										// Declare print method
		int get_num() { return num_; }									// Define accessor method for num_
		void execute();													// Declare execute method
		int get_maxQueue() { return maxQueue; }							// Accessor for max queue stat
		double get_totalArrivalTime() { return totalArrivalTime; }		// Accessor for total arrival time stat

	private:
		int num_; 								// Count of customers generated
		double mean_;							// Customer inter-arrival time
		Queue<Customer> * Q;					// Access to the shared queue
		Server * S1;							// Access to the first server
		Server * S2;							// Access to the second server
		Simulator * sim_;						// Access to the simulator
		int count_;								// When to stop generating customers
		int maxQueue;							// Stat for max queue
		double totalArrivalTime;				// Stat for total arrival time

		std::random_device rd;                  // Create random device
		std::default_random_engine gen; 		// Generator of random numbers
		std::exponential_distribution<> exp; 	// Object for getting values from a particular distribution
};
