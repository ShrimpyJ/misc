#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
using namespace std;

enum hex{'0

int main()
{
	int num = 1128;
	int div = num;
	char *hex_val;
	while (div){
		char *c;
		double tmp = (double)(div / 16.0);
		div = div / 16;
		int rem  = (tmp - div) * 16;
		switch(rem){
			case 10:
				*c = 'A';
				break;
			case 11:
				*c = 'B';
				break;
			case 12:
				*c = 'C';
				break;
			case 13:
				*c = 'D';
				break;
			case 14:
				*c = 'E';
				break;
			case 15:
				*c = 'F';
				break;
			default:
				*c = static_cast<char>(rem);
		}
		strcat(hex_val, c);
	}

	cout << hex_val << endl;
	return 0;
}
