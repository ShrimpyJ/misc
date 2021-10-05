#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

class Timestamp
{
public:
	int hour,min,sec,ms;
};

Timestamp operator+(const Timestamp ts1, const Timestamp ts2);
Timestamp operator-(const Timestamp ts1, const Timestamp ts2);
ostream& operator<<(ostream &os, const Timestamp ts);

int main()
{
	Timestamp ts1 = {8,1,30,0};
	Timestamp ts2 = {8,48,15,12};
	Timestamp ts3 = ts1+ts2;
	cout << ts3;
	ts3 = ts2-ts1;
	cout << ts3;
	return 0;
}

ostream& operator<<(ostream &os, const Timestamp ts)
{
	os << "Time: ";
	os << setw(2) << setfill('0') << ts.hour << ":";
	os << setw(2) << setfill('0') << ts.min << ":";
	os << setw(2) << setfill('0') << ts.sec << ":";
	os << setw(3) << setfill('0') << ts.ms << endl;
}

Timestamp operator+(const Timestamp ts1, const Timestamp ts2)
{
	Timestamp ts3 = {0,0,0,0};
	ts3.ms = ts1.ms + ts2.ms;
	if (ts3.ms >= 1000){
		ts3.ms -= 1000;
		ts3.sec += 1;
	}
	ts3.sec += ts1.sec + ts2.sec;
	if (ts3.sec >= 60){
		ts3.sec -= 60;
		ts3.min += 1;
	}
	ts3.min += ts1.min + ts2.min;
	if (ts3.min >= 60){
		ts3.min -= 60;
		ts3.hour += 1;
	}
	ts3.hour += ts1.hour + ts2.hour;
	return (ts3);
}

Timestamp operator-(const Timestamp ts1, const Timestamp ts2)
{
	Timestamp ts3 = {0,0,0,0};
	int secCarry = 0, minCarry = 0, hourCarry = 0;
	ts3.ms = ts1.ms - ts2.ms;
	if (ts3.ms < 0){
		ts3.ms = 1000 - abs(ts3.ms);
		secCarry = 1;
	}

	ts3.sec = ts1.sec - ts2.sec - secCarry;
	if (ts3.sec < 0){
		ts3.sec = 60 - abs(ts3.sec);
		minCarry = 1;
	}

	ts3.min = ts1.min - ts2.min - minCarry;
	if (ts3.min < 0){
		ts3.min = 60 - abs(ts3.min);
		hourCarry = 1;
	}

	ts3.hour = ts1.hour - ts2.hour - hourCarry;
	if (ts3.hour < 0){
		cout << "Error: Negative answer" << endl;
	}
	return (ts3);
}
