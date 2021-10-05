#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int MAX_TOWERS = 3;
const int MAX_DISKS = 8;

void getInfo(int& n, int& choice);
void move(int n,char src,char dest,char spare, struct Towers tower[], int numDisks);
int getNum(char ch);
void moveDisks(int srcNum, int destNum, struct Towers tower[], int numDisks);
void print(struct Towers tower[], int n);
void userInput(int& srcNum, int& destNum);
bool isValidMove(struct Towers tower[], int srcNum, int destNum, int numDisks);

struct Towers
{
	int index[MAX_DISKS];
};

int main()
{
	//number of disks (will be altered by move function)
	int n;
	//user decision to play or see solution
	int choice;
	//get number of disks and choice from user
	getInfo(n, choice);

	//copy of n that will not be altered by recursive move function
	int numDisks = n;

	Towers tower[MAX_TOWERS];

	//initalize towers 
	for (int i = 0; i < n; i++){
		tower[0].index[i] = i;
		tower[1].index[i] = -1;
		tower[2].index[i] = -1;
	}

	//let user play
	if (choice == 1){
		int srcNum, destNum;
		print(tower, numDisks);

		//main game loop to execute while unsolved
		while (tower[2].index[0] != 0){
			userInput(srcNum, destNum);
			bool isValid = isValidMove(tower, srcNum, destNum, numDisks);
			if (!isValid){
				cout << "Invalid Move. Try Again.\n";
			}
			else if (isValid){
				moveDisks(srcNum, destNum, tower, numDisks);
				print(tower, numDisks);
			}
		}
	}
	
	//show solution
	if (choice == 2){
		print(tower, numDisks);
		cin.clear();
		cin.ignore();
		char src = 'A';
		char spare = 'B';
		char dest = 'C';
		
		move(n, src, dest, spare, tower, numDisks);
		print(tower, numDisks);
	}

	cout << "Victory!\n\n";
	return 0;
}

//get number of disks from user and choice to play or see solution
void getInfo(int& n, int& choice)
{
	bool valid = 0;
	cout << "\n\n   Welcome to Tower of Hanoi!\n\n";
	//get number of disks
	while (valid == 0){
		cout << "Enter number of disks (1 through 8): ";
		cin >> n;
		valid = static_cast<bool>(cin);
		if (n >= 1 && n <= 8){
			valid = 1;
		}
		else if (!valid){
			cout << "Invalid input\n";
			cin.clear();
			while(cin.get() != '\n');
		}
		else{
			valid = 0;
			cout << "Invalid number\n";
		}
	}
	valid = 0;
	//get choice to play or see solution
	while (valid == 0){
		cout << "Press 1 to play yourself\nPress 2 to see solution\nInput: ";
		cin >> choice;
		valid = static_cast<bool>(cin);
		if (choice == 1 || choice == 2){
			valid = 1;
		}
		else if (!valid){
			cout << "Invalid input\n";
			cin.clear();
			while(cin.get()!= '\n');
		}
		else{
			valid = 0;
			cout << "Invalid number\n";
		}
	}
}

//recursively move the disks across towers
void move(int n,char src,char dest,char spare, struct Towers tower[], int numDisks)
{
	//will hold index values of source and destination towers
	int srcNum;
	int destNum;

	if (n == 1){
		cin.ignore();
		srcNum = getNum(src);
		destNum = getNum(dest);
		moveDisks(srcNum, destNum, tower, numDisks);
		print(tower, numDisks);
		cout << src << " to " << dest << "\n\n\n";
		return;
	}
	move(n-1, src, spare, dest, tower, numDisks);
	move(1, src, dest, spare, tower, numDisks);
	move(n-1, spare, dest, src, tower, numDisks);
}

//translate chars into numbers for index of towers
int getNum(char ch)
{
	if (ch == 'A' || ch == 'a'){
		return 0;
	}else if (ch == 'B' || ch == 'b'){
		return 1;
	}else{
		return 2;}
}

//move top disk from one tower to another based on move function
void moveDisks(int srcNum, int destNum, struct Towers tower[], int numDisks)
{
	//will hold the disk from source tower
	int temp;

	//index
	int i = 0;

	int maxIndex = numDisks - 1;
	
	//scan down source tower until top disk is reached
	while (tower[srcNum].index[i] == -1){
		i++;
	}

	//set temp to value of top disk and "remove" top disk by setting to -1
	temp = tower[srcNum].index[i];
	tower[srcNum].index[i] = -1;


	i = 0;
	//scan down destination tower until either top disk is reached or last index
	while (tower[destNum].index[i] == -1 && i < maxIndex){
		i++;
	}

	//if tower is empty place temp disk at bottom
	if (tower[destNum].index[i] == -1){
		tower[destNum].index[i] = temp;
	}
	//else place temp disk on top of indexed disk
	else{
		tower[destNum].index[i-1] = temp;
	}
}


void userInput(int& srcNum, int& destNum)
{
	bool valid = 0;
	char src, dest;
	while(valid == 0){
		cout << "Enter source tower(A, B, C): ";
		cin >> src;
		if (src != 'A' && src != 'a' && src != 'B' && src != 'b' && src != 'C' && src != 'c'){
			cout << "Invalid input. Try again.\n";
		}
		else{
			valid = 1;
		}
	}
	valid = 0;
	while (valid == 0){
		cout << "Enter destination tower(A, B, C): ";
		cin >> dest;
		if (dest != 'A' && dest != 'a' && dest != 'B' && dest != 'b' && dest != 'C' && dest != 'c'){
			cout << "Invalid input. Try again.\n";
		}
		else{
			valid = 1;
		}
	}
	srcNum = getNum(src);
	destNum = getNum(dest);
}

bool isValidMove(struct Towers tower[], int srcNum, int destNum, int numDisks)
{
	//check if source and destination towers are the same
	if (srcNum == destNum){
		return false;
	}

	//will hold the disk from source tower
	int temp;

	//index
	int i = 0;
	int maxIndex = numDisks - 1;
	
	//scan down source tower until either top disk is reached or last index
	while (tower[srcNum].index[i] == -1 && i < maxIndex){
		i++;
	}
	//if source tower is empty, move is automatically invalid
	if (tower[srcNum].index[i] == -1){
		return false;
	}

	//set temp to value of top disk from source tower 
	temp = tower[srcNum].index[i];


	i = 0;
	//scan down destination tower until either top disk is reached or last index
	while (tower[destNum].index[i] == -1 && i < maxIndex){
		i++;
	}

	//if destination tower is empty, move is automatically valid
	if (tower[destNum].index[i] == -1){
		return true;
	}
	//if disk exists at destination tower, check if larger than source disk
	else if (tower[destNum].index[i] > temp){
		return true;
	}
	//else if destination disk is smaller than source disk, move is invalid
	else{
		return false;
	}
}

//print towers to screen
void print(struct Towers tower[], int n)
{
	//set default width
	int width = n * 2 + 2;
	int def = width;

	//track the offset in width caused by disks
	int offsetNow;
	int offsetPrev = 0;

	//empty tower section
	string rod = "|";

	//disks on tower
	//each disk corresponds directly to the struct's index
	//so disk 0 ("-") == index[0]     disk 1 ("---") == index[1]    etc.
	string disk[MAX_DISKS] = {"-", "---", "-----", "-------",
	                          "---------", "-----------",
				  "-------------", "---------------"};

	//print the towers from top to bottom, left to right
	for (int i = 0; i < n; i++){     //top to bottom
		for (int j = 0; j < MAX_TOWERS; j++){   //left to right

			//if disk exists at current index (index != -1)
			if (tower[j].index[i] != -1){
				//set current width offset to index
				offsetNow = tower[j].index[i];
				
				//always set leftmost tower's width independent of offsetPrev
				if (j == 0){
					width = width + tower[j].index[i];
				}

				//for other two towers, calculate necessary width for
				//alignment based off current disk width and previous disk width
				else if (offsetNow > offsetPrev){
					width = width + (offsetNow - offsetPrev);
				}
				else{
					width = width - (offsetPrev - offsetNow);
				}

				//print the disk using new calculated width
				cout << setw(width) << disk[tower[j].index[i]];
				//set current offset to offsetPrev for next tower's calculation
				offsetPrev = tower[j].index[i];
			}

			//else (if disk does not exist at current index)
			else{
				//if current tower is not the leftmost
				//calculate necessary width based off previous disk's width
				if (j != 0){
					width -= offsetPrev;
				}
				//print empty tower segment
				cout << setw(width) << rod;
				//empty segments cause no width offset, so set Prev to 0
				offsetPrev = 0;
			}
			//reset width to default
			width = def;
		}
		//begin next row
		cout << '\n';
	}

	//print base of each tower
	int baseWidth = n * 2 + 1;
	string base = "+";
	cout << setw(width / 2 + 1);

	for (int i = 0; i < MAX_TOWERS; i++){
		for (int j = 0; j < baseWidth; j++){
			cout << base << setw(1);;
		}
		cout << ' ';
	}
	cout << '\n';
}
