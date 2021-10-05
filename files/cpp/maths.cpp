#include <iostream>
#include <cmath>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

char getSign(int n, int x);
void doMath(vector<double> &arr, vector<char> &ch, char sign, char sign2);

random_device rd;
mt19937 gen(rd());
int rollDie(int low, int high)
{
	uniform_int_distribution<> distr(low, high);
	return distr(rd);
}

int main()
{
	vector<double> arr;   //numbers in generated problem
	vector<int> ops;      //
	vector<char> ch;

	while (true){
		int r = rollDie(5,10);

		//get numbers
		for (int i = 0; i < r; i++){
			int x = rollDie(1,472);   //get random # betweeen 1 and 472 inclusive
			arr.push_back(x);
			int y = rollDie(1,100);   //roll for random operator
			ops.push_back(y);
		}
		
		ops.pop_back();   //remove unnecessary last sign occurring after final number

		//print
		for (int i = 0; i < r; i++){
			if (i != r-1){
				char c = getSign(ops[i],arr[i+1]);
				ch.push_back(c);
			}
			else{
				ch.push_back('\n');
			}
			cout << arr[i] << " " << ch[i] << " ";
		}
		cin.ignore();

		//get answer
		doMath(arr,ch,'^','N');  //Exponent step ('N' is NULL)
		doMath(arr,ch,'*','/');  //Multiply and Divide step
		doMath(arr,ch,'+','-');  //Add and Subtract step

		cin.ignore();
		cout << arr[0] << endl << endl << endl;

		arr.clear();  ops.clear();  ch.clear();
	}

	return 0;
}

void doMath(vector<double> &arr, vector<char> &ch, char sign, char sign2)
{
	for (int i = 0; i < arr.size(); i++){
		if (ch[i] == sign || ch[i] == sign2){
			switch(ch[i])
			{
			case '^':
				arr[i] = pow(arr[i],arr[i+1]);
				break;
			case '*':
				arr[i] = arr[i] * arr[i+1];
				break;
			case '/':
				arr[i] = arr[i] / arr[i+1];
				break;
			case '+':
				arr[i] = arr[i] + arr[i+1];
				break;
			case '-':
				arr[i] = arr[i] - arr[i+1];
				break;
			}
			arr.erase(arr.begin() + i + 1);
			ch.erase(ch.begin() + i);
			i = -1;
		}
	}
}

char getSign(int n, int x)
{
	if (n >= 1 && n <= 25){
		if (x > 1 && x < 3){
			return '^';
		}
		return '+';
	}
	else if (n >= 26 && n <= 50){
		return '-';
	}
	else if (n >= 51 && n <= 70){
		return '*';
	}
	else if (n >= 71 && n <= 85){
		return '/';
	}
	else if (n >= 86 && n <= 97){
		if (x > 1 && x < 3){
			return '^';
		}
		return '+';
	}
	else if (n >= 98 && n <= 100){
		return '*';
	}
}
