#include <iostream>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ncurses.h>
#include <cstdlib>
#include <string.h>
#include <sstream>

using namespace std;

int Y_POS = 9;
int X_POS = 20;
int MAX_CURS = X_POS-3;

void printScreen(WINDOW *win, vector<double> stack);
void userInput(bool &done, char* input, int &x, int &y, WINDOW *win, vector<double> stack);
void doMath(WINDOW *win, char ch, vector<double> &stack)
{
	double x = stack[stack.size()-2];
	double y = stack[stack.size()-3];
	double z;
	switch(ch)
	{
	case '+':
		z = y + x;
		break;
	case '-':
		z = y - x;
		break;
	case '*':
		z = y * x;
		break;
	case '/':
		z = y / x;
		break;
	}
	stack.pop_back();
	stack.pop_back();
	stack.push_back(z);
}

int getX(WINDOW *win)
{
	int x, y;
	getyx(win,y,x);
	return x;
}

int getY(WINDOW *win)
{
	int x, y;
	getyx(win,y,x);
	return y;
}

void printReg(WINDOW *win)
{
	for (int i = 1; i < Y_POS-2; i++){
		mvwprintw(win, Y_POS-(i+2), 1, "%d:", i);
	}
}

void printBorder(WINDOW *win)
{
	for (int i = 0; i < Y_POS; i++){
		for (int j = 0; j < X_POS; j++){
			if (i == 0 || i == Y_POS-1){
				mvwprintw(win, i, j, "-");
			}
			if (j == 0 || j == X_POS-1){
				mvwprintw(win, i, j, "|");
			}
		}
	}
	printReg(win);
}


void printLine(WINDOW *win, char* input)
{
	if (strlen(input) <= MAX_CURS){
		mvwprintw(win, Y_POS-2, 1, "%s", input);
		printBorder(win);
		return;
	}

	//scroll
	char temp[X_POS];
	int x = getX(win);
	for (int i = 0; i < x; i++){
		temp[i] = input[strlen(input)-MAX_CURS+i];
	}
	mvwprintw(win, Y_POS-2, 1, "%s", temp);
	printBorder(win);
}

void removeChar(char* input, int pos)
{
//	memmove(&input[pos], &input[pos+1], strlen(input) - pos);
	input[strlen(input)-1] = '\0';
}

void addChar(char* input, const char ch[], int pos)
{
	strcat(input, ch);
}

int main()
{
	//ncurses setup
	initscr();
	//cbreak();
	keypad(stdscr, TRUE);
	noecho();
	WINDOW *win = newwin(Y_POS, X_POS, 0, 0);
	nodelay(win, TRUE);
	keypad(win, TRUE);

	char input[150] = "\0";
	double n;
	vector<double> stack;

	do{
		bool done = 0;
		int x = 1;
		int y = Y_POS - 2;
		do{
			userInput(done,input,x,y,win,stack);
		}while(done == 0);
		wclear(win);

		stringstream convert;
		convert << input;
		convert >> n;
		stack.push_back(n);
		memset(input, 0, 150);
		printScreen(win, stack);
	}while(input != "q");
	endwin();

	return 0;
}

void printScreen(WINDOW *win, vector<double> stack)
{
	wclear(win);
	wrefresh(win);
	for (int i = 0; i < stack.size(); i++){
		mvwprintw(win, Y_POS-3-i, 3, "%lf", stack[stack.size()-i-1]);
	}
}

void userInput(bool &done, char* input, int &x, int &y, WINDOW *win, vector<double> stack)
{
	if (x <= 0){
		x = 1;
	}
	if (x > MAX_CURS+1){
		x = MAX_CURS+1;
	}
	wmove(win,y,x);
	int key = wgetch(win);
	switch(key)
	{
	case 10:    //KEY_ENTER
		done = 1;
		break;
	case KEY_BACKSPACE:
		removeChar(input,x-2);
		wclear(win);
		if (strlen(input) < MAX_CURS){
			x--;
		}
		break;
	case '+':
		doMath(win,'+',stack);
		done = 1;
		break;
	case '-':
		doMath(win,'-',stack);
		done = 1;
		break;
	case '*':
		doMath(win,'*',stack);
		done = 1;
		break;
	case '/':
		doMath(win,'/',stack);
		done = 1;
		break;
	case '0':
		addChar(input, "0", x);
		x++;
		break;
	case '1':
		addChar(input, "1", x);
		x++;
		break;
	case '2':
		addChar(input, "2", x);
		x++;
		break;
	case '3':
		addChar(input, "3", x);
		x++;
		break;
	case '4':
		addChar(input, "4", x);
		x++;
		break;
	case '5':
		addChar(input, "5", x);
		x++;
		break;
	case '6':
		addChar(input, "6", x);
		x++;
		break;
	case '7':
		addChar(input, "7", x);
		x++;
		break;
	case '8':
		addChar(input, "8", x);
		x++;
		break;
	case '9':
		addChar(input, "9", x);
		x++;
		break;
	}
	wrefresh(win);
	printLine(win, input);
}

//			case KEY_LEFT:
//				if (x == 1 && strlen(input) + scroll > MAX_CURS){
//					scroll -= 1;
//				}
//				x--;
//				break;
//			case KEY_RIGHT:
//				if (x <= strlen(input)){
//					if (x >= X_POS-2 && scroll < 0){
//						wclear(win);
//						wrefresh(win);
//						scroll += 1;
//					}
//					x++;
//				};
//				break;
