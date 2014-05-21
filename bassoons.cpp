// HW10: Command Line Accessor for Simulator
// Peter Hurford and Bryan Fowler

#include <iostream>
#include "Simulator.h"
using namespace std;

int main() {
	int Bassoons, tolerance;
	double arrivalMean, serviceMean, failureRate;
	
	cout << endl << endl << endl << endl << endl << endl;
	cout << "			Welcome to Dr. Bressoud's Bassoon Saloon!" << endl << endl;
	cout << "Condratulations, you have just been hired as a Supervisor!" << endl;
	cout << "Your job will be to hire and oversee two workers as they manufacture a number of Bassoons. You will decide how many bassoons will be created during a shift and how often your workers will recieve orders for bassoons. When hiring, you will decide how long it takes the workers to complete a bassoon and how efficient they will be in avoiding mistakes. Finally, you will serve as the company's quality control department, deciding how many times a bassoon can be messed up before it is thrown out." << endl << endl;
	
	cout << "____ many basoons will be produced. (integer)" << endl << ">>> ";
	cin >> Bassoons;
	cout << "A bassoon will be requested every ____ minutes." << endl << ">>> ";
	cin >> arrivalMean;
	cout << "It will take ____ minutes to create a bassoon." << endl << ">>> ";
	cin >> serviceMean;
	cout << "The worker will make a mistake ____ percent of the time." << endl << ">>> ";
	cin >> failureRate;
	cout << "You will throw out a bassoon after ____ failures of service." << endl << ">>> ";
	cin >> tolerance;
	cout << endl << endl;
	
	if (cin.fail()) {												// Checks input to match type. <stackoverflow.com/questions/382491/error-handling-in-c>
		cerr << "\nERROR: Precondition not met.  Input must be integer or double.  Program aborted." << endl;
	}
	else {
		cout << Bassoons << " bassoons, arrival mean = " << arrivalMean << ", service mean " << serviceMean << ", failure rate = " << failureRate << "%, tolerance = " << tolerance << endl << endl << endl << endl;
		failureRate = failureRate / 100;
		Simulator sim;
		sim.setup(Bassoons, arrivalMean, serviceMean, failureRate, tolerance);
		sim.doAllEvents();
	}
}
