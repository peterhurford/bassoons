// HW8: Customer Class for DES
// Peter Hurford and Ruijun Ma

#include "Customer.h"
#include <iostream>
#include <sstream>
using namespace std;

string Customer::str() const {			// define print function
	// post: returns a string object of the form <Customer l: value>, where l is the label, and value is the time.
	stringstream s;
	s << "<Customer " << label_ << ": " << time_ << ">"; // see <http://stackoverflow.com/questions/191757/c-concatenate-string-and-int>
	return s.str();
}

double Customer::time() const {			// define accessor for time value
	// post: returns time value
	return time_;
}

string Customer::label() const {		// define accessor for label
	// post: returns label
	return label_;
}

void Customer::setTime(double time) {	// define mutator for time value
	// pre: time is a number
	// post: sets time to the new time value
	time_ = time;
}