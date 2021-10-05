#include <iostream>
#include <ctime>
#include <string>
#include <cmath>
#include <bitset>
#include <chrono>
using namespace std;

void calcTime (long double estimate);

int main(){
	const unsigned long long int max = 25;
	srand(time(0));
	unsigned long long int p = pow(2, max);
	string random;
	string guess;
	string lock;
	unsigned long long int count = 0;
	int r;
	long double estimate = 9.6;
	//generate binary string
	for (int i = 0; i < max; i++){
		r = rand() % 2;
		if (r == 0){
			random = "0";
		}else if (r == 1){random = "1";}
		lock += random;
	}
	//get estimated time to crack
	if (max == 24){
		estimate = 9.6;
	}else if (max < 24){
		for (int i = 24; i != max; i--){
			estimate = estimate / 2;
		}
	}else if (max > 24){
		for (int i = 24; i != max; i++){
			estimate = estimate * 2;
		}
	}
	cout << "Combination: " <<lock << endl;
	cout << "Number of possible combinations: " << p << endl;
	calcTime (estimate);
	cin.ignore();
	auto t1 = chrono::high_resolution_clock::now();
	cout << "Cracking....\n";
	while (guess != lock){
		guess = "";
		count += 1;
		for (int i = 0; i < max; i++){
			r = rand() % 2;
			if (r == 0){
				random = "0";
			}else if (r == 1){random = "1";}
			guess += random;
		}
		cout << lock << endl << guess << endl;
		if (guess !=lock){
			cout << "Try again\n";
			cin.ignore();
		}
	}
	auto t2 = chrono::high_resolution_clock::now();
	auto seconds = chrono::duration_cast<chrono::seconds>(t2-t1).count();
	int mins = 0;
	int hours = 0;
	cout << "Success!\n";
	cout << "Combination is: " << lock << endl;
	cout << "Attempts: " << count << endl;
	if (seconds >= 60){
		mins = seconds / 60;
		seconds = seconds % 60;
	}
	if (mins >= 60){
		hours = mins / 60;
		mins = mins % 60;
	}
	cout << "Time to crack: " << hours << "h" << mins << "m" << seconds << "s\n";
	return 0;
}

void calcTime (long double estimate){
	long long int estHrs = 0, estMins = 0, estSecs = 0;
	long long int estDays = 0, estWeeks = 0, estMonths = 0, estYears = 0;
	estSecs = estimate;
	if (estSecs >= 60){
		estMins = estSecs / 60;
		estSecs = estSecs % 60;
	}if (estMins >= 60){
		estHrs = estMins / 60;
		estMins = estMins % 60;
	}if (estHrs >= 24){
		estDays = estHrs / 24;
		estHrs = estHrs % 24;
	}if (estDays >= 7){
		estWeeks = estDays / 7;
		estDays = estDays % 7;
	}if (estWeeks >= 4){
		estMonths = estWeeks / 4;
		estWeeks = estWeeks % 4;
	}if (estMonths >= 12){
		estYears = estMonths / 12;
		estMonths = estMonths % 12;
	}
	if (estYears == 0 && estMonths == 0 && estWeeks == 0 && estDays == 0){
		cout << "Estimated time: " << estHrs << "h" << estMins << "m" << estSecs << "s\n";
	}else if (estYears == 0 && estMonths == 0 && estWeeks == 0){
		cout << "Estimated time: " << estDays << " days "
			 << estHrs << "h" << estMins << "m" << estSecs << "s\n";
	}else if (estYears == 0 && estMonths == 0){
		cout << "Estimated time: " << estWeeks << " weeks " << estDays << " days "
			 << estHrs << "h" << estMins << "m" << estSecs << "s\n";
	}else if (estYears == 0){
		cout << "Estimated time: " << estMonths << " months " << estWeeks << " weeks " << estDays << " days "
			 << estHrs << "h" << estMins << "m" << estSecs << "s\n";
	}else {
		cout << "Estimated time: " << estYears << " years " << estMonths << " months " << estWeeks << " weeks " << estDays << " days "
			 << estHrs << "h" << estMins << "m" << estSecs << "s\n";

	cout << "Estimated time: " << estYears << " years " << estMonths << " months " << estWeeks << " weeks " << estDays << " days "
		 << estHrs << "h" << estMins << "m" << estSecs << "s\n";
	}
}
