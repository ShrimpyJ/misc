#include <iostream>
using namespace std;
int main(){
	double x;
	cout.setf (ios::fixed | ios::showpoint);
	cout.precision(11);
	cout << "Enter any integer: ";
	cin >> x;
	cin.ignore();
	for (int i = 0; i < 100; i++){
		x = 1 + 1.0 / x;
		cout << x;
		cin.ignore();
	}
}
