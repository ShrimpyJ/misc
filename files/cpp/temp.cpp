#include <iostream>
#include <cmath>
using namespace std;

const double F1 = -42.379;
const double F2 = 2.04901523;
const double F3 = 10.14333127;
const double F4 = -0.22475541;
const double F5 = -6.83783 * pow(10, -3);
const double F6 = -5.481717 * pow(10, -2);
const double F7 = 1.22874 * pow(10, -3);
const double F8 = 8.5282 * pow(10, -4);
const double F9 = -1.99 * pow(10, -6);

const double C1 = -8.78469475556;
const double C2 = 1.61139411;
const double C3 = 2.33854883889;
const double C4 = -0.14611605;
const double C5 = -0.012308094;
const double C6 = -0.016428277778;
const double C7 = 0.002211732;
const double C8 = 0.00072546;
const double C9 = -0.000003582;

int main(){
	char selection;
	double temp, humidity, final, tempF;

    cout.setf (ios::fixed | ios::showpoint);
    cout.precision(1);
	cout << "Press 'f' for farenheit or 'c' for celcius: ";
	cin >> selection;
	if (selection == 'f'){
		cout << "Enter temperature in farenheit: ";
		cin >> temp;
		cout << "Enter humidity: ";
		cin >> humidity;
		final = F1 + (F2 * temp) + (F3 * humidity) + (F4 * temp * humidity) 
                + (F5 * pow(temp, 2)) + (F6 * pow(humidity, 2)) + 
                (F7 * pow(temp, 2) * humidity) + (F8 * temp * pow(humidity, 2)) 
                + (F9 * pow(temp, 2) * pow(humidity, 2));
        tempF = (final - 32) / 1.8;
		cout << "Heat index is about\n" << final << " degrees f\n" << tempF << " degrees c\n";
		cout << temp << endl;
		cout << humidity << endl;
	}else if (selection == 'c'){
		cout << "Enter temperature in celcius: ";
		cin >> temp;
		cout << "Enter humidity: ";
		cin >> humidity;
		final = C1 + (C2 * temp) + (C3 * humidity) + (C4 * temp * humidity) 
                + (C5 * pow(temp, 2)) + (C6 * pow(humidity, 2)) + 
                (C7 * pow(temp, 2) * humidity) + (C8 * temp * pow(humidity, 2)) 
                + (C9 * pow(temp, 2) * pow(humidity, 2));
		cout << "Heat index is about " << final << " degrees c\n";
		cout << temp << endl;
		cout << humidity << endl;
	}
	return 0;
}
