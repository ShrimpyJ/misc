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
void printLines(char array[][200], int sneed[][50], int i, char line[][50]);



int main(){
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	refresh();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elapsed_seconds;
	int numLines = 1010;
	ifstream input;
	srand(time(0));
	char array[numLines][200];
	char line[300][50];
	int sneed[300][50];
	int userInput[300][20];
	int i = 0;
	int j = 0;
	double totalWords;
	double correctWords;
	double accuracy;

	input.open("./typing/words.dat");
	while (!input.eof()){
		input.getline(array[i], 50);
		i++;
	}
	input.close();

	printLines(array, sneed, i, line);
	refresh();
	i = 0;
	int n = 60;
	int jPrev = 0;
	start = chrono::system_clock::now();
	noecho();
	do{
		attron(COLOR_PAIR(2));
		int totalChars = 0;
		int j = 0;
		while ((userInput[i][j] = getch()) != ' '){
			if (userInput[i][j] != KEY_BACKSPACE){
				noecho();
				if (userInput[i][j] == sneed[i][j]){
					totalChars += 1;
					addch(userInput[i][j]);
				}else if (userInput[i][j] != sneed[i][j]){
					attron(COLOR_PAIR(1));
					addch(userInput[i][j]);
				}
				j++;
			}else if (userInput[i][j] == KEY_BACKSPACE){
				delch();
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
		}
		addch(' ');
		jPrev = j;
		if (totalChars == j && userInput[i][0] != ' '){
			correctWords += 1;
		}
			totalWords += 1;
		i++;
		end = chrono::system_clock::now();
		elapsed_seconds = end - start;
//	}while (elapsed_seconds.count() < n);
	}while(i < 5);
	accuracy = correctWords / totalWords * 100;
	refresh();
	cout << "Correct Words: " << correctWords << endl
		 << "Accuracy: " << accuracy << "%" << endl;
	napms(5000);
	getch();
	endwin();

	return 0;
}

void printLines(char array[][200], int sneed[][50], int i, char line[][50]){
	int maxLines = i - 2;
	for (i = 0; i < 300; i++){
		int r = rand() % maxLines;
		for (int j = 0; j < 50; j++){
			sneed[i][j] = array[r][j];
			addch(array[r][j]);
		}
		if (i % 15 == 0){
			printw("\n\n");
		}
//		strcat(line[i], array[r]);
//		printw(line[i]);
//		printw(" ");
	}
	printw("\n");
}
