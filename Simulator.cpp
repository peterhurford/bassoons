// HW10: Simulator Class
// Peter Hurford and Bryan Fowler

#include "Simulator.h"
#include "Server.h"
#include "CustomerArrival.h"
#include <iostream>

Simulator::Simulator() {
	/*  Constructor initializes data members for the object, but defers to the setup
		method for the creation of the top level objects of the simulated system.	   			*/
	vtime_ = 0;							// Start simulator at t = 0
	C = NULL;
	S1 = NULL;
	S2 = NULL;
	Q = NULL;
}

Simulator::~Simulator() {			// Define Destructor					
	delete Q;
	delete C;
	delete S1;
	delete S2;
}

double Simulator::now() const { return vtime_; } 		// Return value of current virtual time


int Simulator::insert(Event * e) {
	/* 	Takes pointer to event and inserts it into the OrderedSet maintained by the simulation,
		returning the OrderedSet's return value indicating success or failure of the insertion.  */

	int r = events.insert(e);			// Insert event pointer into the OrderedSet using the OrderedSet's insert method.
	return r;							// Return the success or failure value created by the OrderedSet's insert method.
} 		
 

void Simulator::doAllEvents() {
	/*	Main driver of the simulation object, wherein it repeatedly removes the
		first event from the OrderedSet, updates virtual time to the time of the event, and
		executes the event. This continues as long as there are events to procesS->			  	*/

	while (events.len() > 0) {							// As long as there are events in the OrderedSet...
		Event * E = events.removeFirst();				// ...Remove the first entry in the OrderedSet
		vtime_ = E->time();								// ...Set simulator time to the time of the event
		E->execute();									// ...Execute the event using that event's execute method.
	}
	
	sink();												// Dump stats
}


void Simulator::sink() {
	cout << "STATS" << endl;
	cout << "                    Total Arrivals:   " << C->get_num() << endl;
	cout << "                    Total Services:   " << S1->get_services() + S2->get_services() << endl;
	cout << "  Total Services from First Server:   " << S1->get_services() << endl;
	cout << " Total Services from Backup Server:   " << S2->get_services() << endl;
	cout << "                        Final Time:   " << now() << endl;
	cout << "          Total Wait Time in Queue:   " << S1->get_totalWaitTime() + S2->get_totalWaitTime() << endl;
	cout << "           Mean Wait Time in Queue:   " << (S1->get_totalWaitTime() + S2->get_totalWaitTime()) / C->get_num() << endl;
	cout << "             Total Time in Service:   " << S1->get_totalServiceTime() + S1->get_totalServiceTime() << endl;
	cout << "        Total Time by First Server:   " << S1->get_totalServiceTime() << endl;
	cout << "       Total Time by Backup Server:   " << S2->get_totalServiceTime() << endl;
	cout << "              Mean Time in Service:   " << (S1->get_totalServiceTime() + S2->get_totalServiceTime()) / C->get_num() << endl;
	cout << "                Total Arrival Time:   " << C->get_totalArrivalTime() << endl;
	cout << "                 Mean Arrival Time:   " << C->get_totalArrivalTime() / C->get_num() << endl;
	cout << "                Server Utilization:   " << ((S1->get_totalServiceTime() + S2->get_totalServiceTime()) / (2*now())) * 100 << "%" << endl;
	cout << "               Mean Time in System:   " << (S1->get_totalWaitTime() + S2->get_totalWaitTime() + S1->get_totalServiceTime() + S2->get_totalServiceTime()) / C->get_num() << endl;
	cout << "               Max Length of Queue:   " << C->get_maxQueue() << endl;
	cout << "              Mean Length of Queue:   " << (S1->get_totalWaitTime() + S2->get_totalWaitTime()) / now() << endl;
	cout << "Mean Number of Customers in System:   " << (S1->get_totalWaitTime() + S2->get_totalWaitTime() + S1->get_totalServiceTime() + S2->get_totalServiceTime()) / now() << endl << endl;
	cout << " Total Failed Services from First Server:   " << S1->get_failures() << endl;
	cout << "Total Failed Services from Backup Server:   " << S2->get_failures() << endl;
	cout << "                   Total Failed Services:   " << S1->get_failures() + S2->get_failures() << endl;
	
	// <stackoverflow.com/question/12447325/dividing-two-integers-to-produce-a-float-result>
	float msf_stat = ((float)S1->get_failures() + (float)S2->get_failures()) / ((float)S1->get_services() + (float)S2->get_services());														
	cout << "                     Mean Server Failure:   " << msf_stat *100 << "%" << endl << endl;
	
	cout << " Total Trashes by First Server:   " << S1->get_trashbin() << endl;
	cout << "Total Trashes by Backup Server:   " << S2->get_trashbin() << endl;
	cout << "                 Total Trashes:   " << S1->get_trashbin() + S2->get_trashbin() << endl;

	float mt_stat = ((float)S1->get_trashbin() + (float)S2->get_trashbin()) / (float)C->get_num();
	cout << "                    Mean Trash:   " << mt_stat * 100 << "%" << endl << endl;
	cout << " Number of successful services:   " << C->get_num() - (S1->get_trashbin() + S2->get_trashbin()) << endl;

	cout << "--------" << endl;
}


int Simulator::pass_num() { return C->get_num(); }		// Define accessor for num_ from CustomerArrival 		
		

void Simulator::setup(int custCount, double arrivalMean, double serviceMean, double failureMean, int tolerance) {
	/*	Takes an integer specifying total count of customers to introduce into the system, and the simulation
		parameters of the mean inter arrival time and the mean service time. The method should create the shared queue,
		the server, and the customer arrival objects with appropriate arguments. Finally, it should insert the customer
		arrival into to simulator to "prime" the future events OrderedSet of the simulation.   */
	// pre: custCount is number of customers to generate, arrivalMean is average time they arrive, service mean is average length of service,
	//      failureMean is percent chance of failed service (up to two decimal places), tolerance is number of failures allowed (tolerance+1 is trashed)

	OrderedSet<Event*> events(2);												// Create ordered set
	Q = new Queue<Customer>(custCount);											// Create shared queue
	S1 = new Server(serviceMean, failureMean, tolerance, Q, this, 1);			// Create server
	S2 = new Server(serviceMean, failureMean, tolerance, Q, this, 2);			// Create server
	C = new CustomerArrival(arrivalMean, Q, S1, S2, this, custCount, vtime_);	// Create the customer arrival
	insert(C);																	// Insert the Customer Arrival into the simulator (ordered set of events)
}
