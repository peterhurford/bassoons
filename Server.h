// HW10: Header for the Server Class
// Peter Hurford and Bryan Fowler

#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <random>
#include "Event.h"
#include "Queue.h"
#include "Simulator.h"
#include "Customer.h"
using namespace std;

class Server: public Event {
    public:
        Server(double mean=7.0, double failureMean = 0.1, int tolerance = 2, Queue<Customer> * queue=NULL, Simulator * sim=NULL, int id = 1) :   //  Define constructor
        exp(1/mean), gen(rd()) { // Initialization list
        mean_ = mean;
        failureMean_ = failureMean;
        tolerance_ = tolerance;
        Q = queue;
        sim_ = sim;
        busy = false;
        count = 0;
        lastStart = 0.0;
        totalServiceTime= 0.0;
        totalWaitTime = 0.0;
        failures = 0;
        services = 0;
        trashbin = 0;
        id_ = id;
    }

    bool available();                                           // Declare accessor for server status
    void startService(Customer & c);                            // Declare startService method
    void execute();                                             // Declare execute method
    double get_totalWaitTime() { return totalWaitTime; }        // Define accessor for stat for total waiting time
    double get_totalServiceTime() { return totalServiceTime; }  // Define accessor for stat for total service time
    int get_failures() { return failures; }						// Define accessor for stat for total failed services
    int get_services() { return services; }						// Define accessor for stat for total services
    void trash() { trashbin++; }								// Define mutator for trashbin
    int get_trashbin() { return trashbin; }						// Define accessor for trashbin
    virtual ~Server() {};                                       // Define destructor (empty because there are no dynamic elements)

    private:
        double mean_;                     // Service time mean
        double failureMean_;			  // Mean amount of failed services (as percentage)
        int tolerance_;					  // Allowed amount of failures before trashing (trash at tolerance+1)
        Queue<Customer> * Q;              // Access to shared queue
        Simulator * sim_;                 // Access to "parent" simulator
        Customer current;                 // Copy of current customer
        bool busy;                        // Boolean maintaining service-in-progress
        int count;                        // Number of customer served
        double lastStart;                 // Time of last start-of-service
        double totalServiceTime;          // Aggregate of all completed service time
        double totalWaitTime;             // Aggregate of all completed wait time
        int maxQueue;                     // Keep record of largest size of queue
        int failures;				  	  // Keep record of number of failed services
        int services;					  // Keep record of total number of services
        int trashbin;					  // Keep record of total amount of trashed variables

        std::random_device rd;                  // Create random device
        std::default_random_engine gen;         // Generator of random numbers
        std::exponential_distribution<> exp;    // Object for getting values from a particular distribution
};

#endif
