#include <iostream>
using namespace std;

int main(){
	int quint = 19729;
	string finalNumber;
	string num = "9";
	for (int i = 0; i <= quint; i++){
		int r = rand() % 9 + 1;
		finalNumber += num;
	}
	cout << "Are ya ready, kids?";
	cin.ignore();
	cout << finalNumber;
	return 0;
}
