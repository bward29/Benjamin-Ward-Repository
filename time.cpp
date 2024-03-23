#include <sstream>
#include <iomanip>
using namespace std;

#include "time.h"
void Time::setHour(int hr) {
	hour = hr; // hour is a member var

}
void Time::setMinute(int min) {
	minute = min; // minute is a member var
}
void Time::addHour() { // a private member func
	if (hour == 12)
	  hour = 1;
	else
	  hour++;
}
void Time::addMinute(){
	if (minute == 59) {
		minute = 0;
		addHour(); // call to private member func
	}     else
		minute++;
}
string Time::display()
	// returns time in string formatted to hh:mm
{
	ostringstream sout;
	sout.fill ('0');
 	sout << hour << ":" << setw(2) << minute;
	return sout.str();
}
