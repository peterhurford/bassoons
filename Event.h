// HW 9/10: Event.h
// Peter Hurford and Bryan Fowler

#ifndef _EVENT_H
#define _EVENT_H
#include <string>

using namespace std;

class Event {
		friend std::ostream& operator<<(std::ostream& os, const Event* e)
		{ os << e->str(); return os; }
	public:
		Event(int id = 0, double time = -1.0);	// constructor  pre: id is an int and time is a double; if not specified, id equals 0 and time equals -1
		virtual ~Event();                       // destructor 
		virtual string str() const;				// declare string method
		double time() const;					// declare accessor for time value
		int id() const;							// declare accessor for id
		bool operator<(const Event &other);		// declare less than operator
		bool operator<=(const Event &other);	// declare less than equal to operator
		bool operator>(const Event &other);		// declare greater than operator
		bool operator>=(const Event &other);	// declare greater than equal to operator
		bool operator==(const Event &other);	// declare equal to operator
		bool operator!=(const Event &other);	// declare not equal to operator
		void setTime(double time);				// declare mutator for time
		virtual void execute();					// declare execute method
	
	protected:
		int id_;
		double time_;
};

#endif
		
