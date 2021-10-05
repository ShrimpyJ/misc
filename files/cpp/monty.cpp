#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;


bool play(bool swap)
{
	int size = 3;
	vector<bool> doors;
	vector<int> empty;
	int r = rand() % size;
	int winner = r;
	for (int i = 0; i < size; i++){
		if (i == r) doors.push_back(1);
		else{
			doors.push_back(0);
			empty.push_back(i);
		}
//		cout << "X ";
	}
//	cout << endl;

	int choice = rand() % size;
	int closed;
	if (doors[choice] == 1){
		r = rand() % empty.size();
		closed = empty[r];
	}
	else closed = winner;

	for (int i = 0; i < size; i++){
//		if (i == closed) cout << "X ";
//		else if (i == choice) cout << "P ";
//		else cout << "0 ";
	}
//	cout << endl;

	r = rand() % 2;
	if (swap == 1){
		choice = closed;
//		cout << "Choice: Switch to " << choice+1 << endl;
	}
//	else cout << "Choice: Stay\n";

	bool victory = 0;
	for (int i = 0; i < size; i++){
//		if (doors[i]) cout << "W ";
//		else cout << "_ ";
		if (choice == i && doors[i] == 1) victory = 1;
	}
//	cout << endl;

//	if (victory) cout << "Victory!\n";
//	else cout << "You lose, try again!\n";

	return victory;
}

int main()
{
	srand(time(NULL));
	double i;
	double j;
	double wi = 0;
	double wj = 0;
	double ri;
	double rj;
	int runs = 500000;
	for (i = 0; i < runs; i++){
		bool b = play(0);
		if (b) wi++;
	}
	ri = wi / i;

	for (j = 0; j < runs; j++){
		bool b = play(1);
		if (b) wj++;
	}
	rj = wj / j;

	cout << "\n   Stay Games Played: " << i << "\n   Wins: " << wi << "\n     Percentage: " << ri * 100.0 << endl;
	cout << "\n   Swap Games Played: " << j << "\n   Wins: " << wj << "\n     Percentage: " << rj * 100.0 << endl;

	return 0;
}
