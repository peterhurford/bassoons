// HW9/10: Event Class
// Peter Hurford and Bryan Fowler

#include "Event.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

Event::Event(int id, double time)			//constructor
{
	id_ = id;
	time_ = time;
}


Event::~Event()
{
	
};                                                      //destructor

string Event::str() const				//string function
{
	string a;
	stringstream s;
	s << "<Event " << id_ << ": " << time_ << ">";
	a = s.str();					//string version of event
	return a;
}

double Event::time() const				//time function
{
	return time_;					//return time of event
}

int Event::id() const					//id function
{
	return id_;					//return id of function	
}

bool Event::operator<(const Event &other)		//less than operator
{
	if (time_ < other.time_){			//if time of event less than time of other
		return true;
	}
	return false;
}

bool Event::operator<=(const Event &other)		//less than or equal to operator
{
	if (time_ <= other.time_){			//if time of event less than or equal to time of other
		return true;
	}
	return false;
}

bool Event::operator>(const Event &other)		//greater than operator
{
	if (time_ > other.time_){			//if time of event greater than time of other
		return true;
	}
	return false;
}

bool Event::operator>=(const Event &other)		//greater than or equal to operator
{
	if (time_ >= other.time_){			//if time of event greater than or equal to time of other
		return true;
	}
	return false;
}

bool Event::operator==(const Event &other)		//equal to operator
{
	if (time_ == other.time_){			//if time of event equal to time of other
		return true;
	}
	return false;
}

bool Event::operator!=(const Event &other)		//not equal to operator
{
	if (time_ != other.time_){			//if time of event not equal to time of other
		return true;
	}
	return false;
}

void Event::setTime(double time)			
{
	time_ = time;					//set time of event
}

void Event::execute()
{
	cout << str() << endl;				//print string version of event
}

