#include<iostream>
#include "time.h"
using namespace std;

int main() {
	Time t;
	t.setHour(12);
	t.setMinute(58);
	cout << t.display() <<endl;
	t.addMinute();
	cout << t.display() <<endl;
	t.addMinute();
	cout << t.display() <<endl;
	return 0;
}
