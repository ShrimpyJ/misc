#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib>

using namespace std;

void addBig(vector<char> &cnum, int n);
void carry(vector<char> &cnum, int i);
ostream& operator<<(ostream &os, const vector<char> &v);

int main()
{
	//unsigned long long int num = 18446744073709551615U;

	//the above number as a char vector (input backwards)
	//vector<char> cnum = {'5','1','6','1','5','5','9','0','7','3','7','0','4','4','7','6','4','4','8','1'};
	vector<char> cnum = {'1'};
	cout << cnum;
	int n = 2;
	int count = 0;

	while (true){
		addBig(cnum, n);
		cout << cnum;
		n += pow(n,3);
		count++;
	}


	return 0;
}

//Takes an "int" as a vector of chars along with a real int to be added to it
//Uses int<->char conversions and single-digit additions to "add" the two #'s together
//Overwrites original "int" vector with the final result
void addBig(vector<char> &cnum, int n)
{
	//convert # being added to vector of chars
	string str = to_string(n);
	vector<char> v(str.begin(), str.end());

	int digits = str.length();    //get number of digits in # being added

	//add empty digits to vector of chars if # being added contains more digits
	if (cnum.size() < digits){
		for (int i = 0; i < digits-1; i++){
			cnum.push_back('0');
		}
	}

	//loop through all digits of # being added (1 loop for 1 digit, 2 loops for 2 digits, etc.)
	for (int i = 0; i < digits; i++){
		int pos = v.size() - (1+i);  //position of digit in # being added
		int num = v[pos] - '0';      //convert digit to int
		int val = cnum[i] - '0';     //convert current digit in original # to int
		int result = num + val;      //add both converted digits together

		//if result of addition is 10 or higher, carry to next digit
		if (result > 9){
			result -= 10;    //subtract base (10) to get a digit 0-9 to be added to current digit
			carry(cnum,i+1); //add 1 to next digit
		}

		//convert result to char and replace position in vector with it
		char c = result + '0';
		cnum[i] = c;
	}
	v.clear();
}

void carry(vector<char> &cnum, int i)
{
	//if # contains no further digits, add one and return
	if (cnum.size() <= i){
		cnum.push_back('1');
		return;
	}

	//otherwise, add 1 to current digit and carry again if needed
	int val = cnum[i] - '0';
	val += 1;
	if (val > 9){
		val -= 10;
		carry(cnum, i+1);
	}
	char c = val + '0';
	cnum[i] = c;
}

ostream& operator<<(ostream &os, const vector<char> &v)
{
	for (int i = v.size(); i >= 0; i--){
		os << v[i];
	}
	os << endl;

	return os;
}
