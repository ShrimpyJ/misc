#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ctime>
#include <chrono>


using namespace std;
void printLines(char array[][200], int sneed[][50], int i); 
void moveLines(int array[][50], int f, int k, bool isCorrect[], bool isCharCorrect[][50]);
void moveUserLines(int array[][50], int f, int k, bool isCorrect[], bool isCharCorrect[][50]);

const int pos = 50;

int main(){
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	refresh();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_BLACK);
	bkgd(COLOR_PAIR(4));


	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elapsed_seconds;
	int numLines = 1010;
	ifstream input;
	srand(time(0));
	char array[numLines][200];
	char endProgram;
	int sneed[300][50];
	int userInput[300][50];
	bool isCorrect[300];
	bool isCharCorrect[300][50];
	int i = 0;
	int j = 0;
	double totalWords;
	double correctWords;
	double accuracy;

	input.open("/home/pete/typing/words.dat");
	while (!input.eof()){
		input.getline(array[i], 50);
		i++;
	}
	input.close();

	printLines(array, sneed, i);
	refresh();
	i = 0;
	int n = 60;
	int jPrev = 0;
	start = chrono::system_clock::now();
	noecho();
	int k = pos;
	do{
		int totalChars = 0;
		int j = 0;
		while ((userInput[i][j] = mvgetch(0, pos)) != ' '){
			if (userInput[i][j] != KEY_BACKSPACE){
				if (userInput[i][j] == sneed[i][j]){
					isCharCorrect[i][j] = 1;
					totalChars += 1;
				}else if (userInput[i][j] != sneed[i][j]){
					isCharCorrect[i][j] = 0;
				}
				k--;
				j++;
			}else if (userInput[0][0] == KEY_BACKSPACE){
				continue;
			}else if (userInput[i][j] == KEY_BACKSPACE){
				k++;
				if (totalChars < j || j == 0){
					j--;
				}else if (totalChars == j){
					j--;
					totalChars -=1;
				}if (j < 0){
					i--;
					j = jPrev;
					totalChars = jPrev;
					totalWords -= 1;
				}
			}
			moveLines(sneed, 0, k, isCorrect, isCharCorrect);
			moveUserLines(userInput, 1, k, isCorrect, isCharCorrect);
		}
		jPrev = j;
		k--;
		if (totalChars == j && isCorrect[i] != 1 && userInput[i][0] != ' '){
			isCorrect[i] = 1;
			correctWords += 1;
		}
		moveLines(sneed, 0, k, isCorrect, isCharCorrect);
		moveUserLines(userInput, 1, k, isCorrect, isCharCorrect);
		totalWords += 1;
		i++;
		end = chrono::system_clock::now();
		elapsed_seconds = end - start;
	}while (elapsed_seconds.count() < n);
//	}while(i < 5);
	accuracy = correctWords / totalWords * 100;
	refresh();
	cout << "Correct Words: " << correctWords << endl
	     << "Accuracy: " << accuracy << "%" << endl;
	refresh();
	cout << "Press Tab to end\n";
	cin.get(endProgram);
	while (endProgram != '\t'){
		cin.get(endProgram);
	}
	endwin();
	return 0;
}

void printLines(char array[][200], int sneed[][50], int i){
	attron(COLOR_PAIR(3));
	int maxLines = i - 2;
	int k = pos;
	for (i = 0; i < 300; i++){
		int r = rand() % maxLines;
		for (int j = 0; array[r][j] != '\0'; j++){
			sneed[i][j] = array[r][j];
			mvaddch(0, k, sneed[i][j]);
			k++;
		}
		k++;
	}
}

void moveLines(int array[][50], int f, int k, bool isCorrect[], bool isCharCorrect[][50]){
	int j = 0;
	int diff = k;
	clear();
	for (int i = 0; i < 250; i++){
		attron(COLOR_PAIR(3));
		for (j = 0; array[i][j] != '\0'; j++){
			mvaddch(f, k, array[i][j]);
			k++;
		}
			addch(' ');
			k++;
	}
}

void moveUserLines(int array[][50], int f, int k, bool isCorrect[], bool isCharCorrect[][50]){
	int j = 0;
	int diff = pos - k;
	for (int i = 0; i < 250; i++){
		if (isCorrect[i] == 1){
			attron(COLOR_PAIR(2));
		}
		for (j = 0; array[i][j] != '\0'; j++){
			if (array[i][j] == KEY_BACKSPACE){
				mvdelch(1, k - 1);
				break;
			}
			if (isCharCorrect[i][j] == 1){
				attron(COLOR_PAIR(2));
			}else if (isCharCorrect[i][j] == 0){
				attron(COLOR_PAIR(1));
			}
			mvaddch(f, k, array[i][j]);
			k++;
		}
	}
}
