#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

struct Queen
{
	int space;
	char name[5];
	vector<int> taken;
};

ostream& operator<<(ostream& os, const vector<int> &totalTaken);
bool recursive(int n, vector<Queen> &qvec, vector<int> &totalTaken);
void addPiece(int num, vector<Queen> &qvec, vector<int> &totalTaken);
void printBoard(vector<int> &totalTaken, vector<Queen> &qvec);
void removePiece(vector<Queen> &qvec, vector<int> &totalTaken);
void getTakenSpaces(vector<Queen> &qvec, vector<int> &totalTaken);
void getNumSpaces(int& up, int& down, int& left, int& right, int space);
bool isTaken(int num, vector<int> &totalTaken);
bool isQueen(int k, vector<Queen> &qvec);
bool isFull(vector<int> &totalTaken);
void getAll(int space, int up, int down, int left, int right, Queen &q);
void getUp(int space, int up, Queen &q);
void getDown(int space, int down, Queen &q);
void getLeft(int space, Queen &q);
void getRight(int space, Queen &q);
void getUL(int space, int up, int left, Queen &q);
void getUR(int space, int up, int right, Queen &q);
void getDL(int space, int down, int left, Queen &q);
void getDR(int space, int down, int right, Queen &q);;


int main()
{
	vector<int> totalTaken;
	vector<Queen> qvec;
	printBoard(totalTaken, qvec);

	bool isVictory = recursive(0, qvec, totalTaken);
	if (isVictory == true){
		cout << "\n\nVictory!!\n\n";
	}
	else{
		cout << "\n\nNo possible solutions\n\n";
	}

	return 0;
}

bool recursive(int n, vector<Queen> &qvec, vector<int> &totalTaken)
{
	if (qvec.size() == 8){
		return true;
	}
	for (int i = 0; i < 8; i++){
		bool is_taken = isTaken(n+1, totalTaken);
		if (is_taken == false){
			cout << "Placing queen at: " << n+1 << endl;
			addPiece(n+1, qvec, totalTaken);
			printBoard(totalTaken, qvec);
			//cin.ignore();
			int t = n;
			while (t == 0 || t % 8 != 0){t++;}
			bool done = recursive(t+i, qvec, totalTaken);
			if (done == true){
				return true;
			}
			removePiece(qvec, totalTaken);
			cout << "Removing queen from: " << n+1 << endl;
		}
	}
	return false;
}

bool isTaken(int num, vector<int> &totalTaken)
{
	for (vector<int>::const_iterator itr=totalTaken.begin(); itr != totalTaken.end(); itr++){
		if(*itr == num){
			return true;
		}
	}
	return false;
}

void addPiece(int num, vector<Queen> &qvec, vector<int> &totalTaken)
{
	Queen q;
	int up, down, left, right;
	int space = num;

	q.space = space;

	q.taken.push_back(q.space);
	getNumSpaces(up, down, left, right, q.space);
	getAll(q.space, up, down, left, right, q);

	qvec.push_back(q);

	getTakenSpaces(qvec, totalTaken);
}

void printBoard(vector<int> &totalTaken, vector<Queen> &qvec)
{
	cout << "   a b c d e f g h\n";
	for(int i = 0; i < 8; i++){
		cout << 8-i << ' ';
		for (int j = 1; j < 9; j++){
			int k = 8 * i + j;
			bool is_totalTaken = isTaken(k, totalTaken);
			bool is_queen = isQueen(k, qvec);
			if (is_queen == true){
				cout << "|X";
			}
			else if(is_totalTaken == true){
				cout << "|-";
			}
			else{
				cout << "| ";
			}
		}
		cout << "|\n";
	}
	cout << "   a b c d e f g h\n";
}

bool isQueen(int k, vector<Queen> &qvec)
{
	for (int i = 0; i < qvec.size(); i++){
		if (qvec[i].space == k){
			return true;
		}
	}
	return false;
}

bool isFull(vector<int> &totalTaken)
{
	int count = 0;
	for (int i = 0; i < 64; i++){
		bool is_taken = isTaken(i+1, totalTaken);
		if (is_taken == true){
			count++;
		}
		else{
			return false;
		}
	}
	return true;
}

void removePiece(vector<Queen> &qvec, vector<int> &totalTaken)
{
	qvec.pop_back();
	totalTaken.clear();
	getTakenSpaces(qvec, totalTaken);
}

void getTakenSpaces(vector<Queen> &qvec, vector<int> &totalTaken)
{
	for (int i = 0; i < qvec.size(); i++){
		for (int j = 0; j < qvec[i].taken.size(); j++){
			totalTaken.push_back(qvec[i].taken[j]);
		}
	}
}

int getUserInput(Queen &q)
{
	cout << "Enter coordinates (0 to remove): ";
	char input[5];
	cin >> input;
	int letter, number;
	switch(input[0]){
		case '0':
			return 0;
		case 'a':
			letter = 1;
			break;
		case 'b':
			letter = 2;
			break;
		case 'c':
			letter = 3;
			break;
		case 'd':
			letter = 4;
			break;
		case 'e':
			letter = 5;
			break;
		case 'f':
			letter = 6;
			break;
		case 'g':
			letter = 7;
			break;
		case 'h':
			letter = 8;
			break;
	}
	switch(input[1]){
		case '1':
			number = 1;
			break;
		case '2':
			number = 2;
			break;
		case '3':
			number = 3;
			break;
		case '4':
			number = 4;
			break;
		case '5':
			number = 5;
			break;
		case '6':
			number = 6;
			break;
		case '7':
			number = 7;
			break;
		case '8':
			number = 8;
			break;
	}
	strcpy(q.name, input);

	return ((8-number) * 8) + letter;
}

void getNumSpaces(int& up, int& down, int& left, int& right, int space)
{
	if (space % 8 != 0){
		up = space / 8;
		down = 8 - up - 1;
		left = space % 8 - 1;
		right = 8 - left - 1;
	}else{
		up = (space / 8) - 1;
		down = 8 - up - 1;
		left = 7;
		right = 0;
	}
}

void getAll(int space, int up, int down, int left, int right, Queen &q)
{
	getUp(q.space, up, q);
	getDown(q.space, down, q);
	getLeft(q.space, q);
	getRight(q.space, q);
	getUL(q.space, up, left, q);
	getUR(q.space, up, right, q);
	getDL(q.space, down, left, q);
	getDR(q.space, down, right, q);
}

void getUp(int space, int up, Queen &q)
{
	for (int i = 0; i < up; i++){
		space -= 8;
		if (space <= 0){break;}
		q.taken.push_back(space);
	}
}

void getDown(int space, int down, Queen &q)
{
	for (int i = 0; i < down+1; i++){
		space += 8;
		if (space > 64){break;}
		q.taken.push_back(space);
	}
}

void getLeft(int space, Queen &q)
{
	while ((space - 1) % 8 != 0){
		space -= 1;
		if (space <= 0){break;}
		q.taken.push_back(space);
	}
}

void getRight(int space, Queen &q)
{
	while (space % 8 != 0){
		space += 1;
		if (space > 64){break;}
		q.taken.push_back(space);
	}
}

void getUL(int space, int up, int left, Queen &q)
{
	for (int i = 0; i < up && i < left; i++){
		space = space - 8 - 1;
		if (space <= 0){break;}
		q.taken.push_back(space);
	}
}

void getUR(int space, int up, int right, Queen &q)
{
	for (int i = 0; i < up && i < right; i++){
		space = (space - 8) + 1;
		if (space > 64){break;}
		q.taken.push_back(space);
	}
}

void getDL(int space, int down, int left, Queen &q)
{
	for (int i = 0; i < down && i < left; i++){
		space = (space + 8) - 1;
		if (space <= 0){break;}
		q.taken.push_back(space);
	}
}

void getDR(int space, int down, int right, Queen &q)
{
	for (int i = 0; i < down && i < right; i++){
		space = (space + 8) + 1;
		if (space > 64){break;}
		q.taken.push_back(space);
	}
}

ostream& operator<<(ostream& os, const vector<int> &totalTaken)
{
	os << "Taken spaces:\n";
	for (vector<int>::const_iterator itr=totalTaken.begin(); itr != totalTaken.end(); itr++){
		os << *itr << " ";
	}
	os << '\n';
	return os;
}
