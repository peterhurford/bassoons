// HW8: Customer Class for DES (Header)
// Peter Hurford and Bryan Fowler

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>

class Customer {
	public:
		friend std::ostream& operator<<(std::ostream& os, const Customer& s) { os << s.str(); return os; }
		Customer(double time = 0.0, std::string label = "") { // define constructor
			// pre: time is numeric, label is a string
			time_ = time;
			label_ = label;
			failures_ = 0;
		}
		std::string str() const;							  // declare print function
		double time() const;								  // declare accessor for time value
		std::string label() const;							  // declare accessor for label
		void setTime(double time);							  // declare mutator for time value
		void fail() { failures_++; }						  // define mutator for failures
		int getfails() { return failures_; }				  // define accessor for failures

	private:					// declare variables
		double time_;
		std::string label_;
		int failures_;
};

#endif
