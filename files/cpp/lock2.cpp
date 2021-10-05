#include <iostream>
#include <ctime>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

int main(){
	srand(time(0));
	int max = 21;
	int p = pow(2, max);
	string random;
	string guess;
	string lock;
	int count = 0;
	int r;
	for (int i = 0; i < max; i++){
		r = rand() % 2;
		if (r == 0){
			random = "0";
		}else if (r == 1){random = "1";}
		lock += random;
	}
	cout << "Combination: " <<lock << endl;
	cout << "Number of possible combinations: " << p << endl;
	cin.ignore();
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
//			cin.ignore();
		}
	}
	cout << "Good job!\n";
	cout << "Attempts: " << count << endl;
	return 0;
}
