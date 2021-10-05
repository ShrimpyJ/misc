#include <iostream>
using namespace std;

int main(){
	int num;
	int bin_value = 0;
	int base = 1;
	int temp = num;
	cin >> num;
	while (temp){
		int last_digit = temp % 2;
		temp = temp / 2;
		bin_value += last_digit * base;
		base = base * 10;
	}
	cout << bin_value << endl;
	return 0;
}
