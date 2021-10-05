#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

using namespace std;

const int MAX = 21;
const int microseconds = 16000;

void moveChar(int move, int& pos);
void printScreen(int pos, WINDOW *win);

int main()
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	WINDOW *win = newwin(50, MAX*3, 1, 1);
	scrollok(win, TRUE);
	nodelay(win, TRUE);
	keypad(win, TRUE);

	int userInput;
	int move = 0;
	int pos = MAX / 2;

	string get = "xset r rate 100 40";
	const char *command = get.c_str();
	system(command);

	//main game loop
	do{
		printScreen(pos,win);
		wrefresh(win);
		userInput = wgetch(win);
		//userInput = getch();
		switch(userInput)
		{
			case KEY_LEFT:
				move = -1;
				moveChar(move, pos);
				break;
			case KEY_RIGHT:
				move = 1;
				moveChar(move, pos);
				break;
		}
		move = 0;
		usleep(microseconds);
	}while(userInput != 'q');
	endwin();

	get = "xset r rate 440 24";
	command = get.c_str();
	system(command);

	return 0;
}

void moveChar(int move, int& pos)
{
	if (move == -1){
		pos -= 1;
		if (pos < 0){
			pos = 0;
		}
		return;
	}
	pos += 1;
	if (pos > MAX-1){
		pos = MAX-1;
	}
}

void printScreen(int pos, WINDOW *win)
{
	for (int i = 0; i < MAX; i++){
		if (i == pos){
			wprintw(win, "*");
		}
		else{
			wprintw(win, "-");
		}
	}
	wprintw(win, "\n");
}

//	while (true){
//		for (int i = 0; i < MAX*2; i++){
//			for (int j = 0; j < MAX; j++){
//				if ((i % MAX) + j == (MAX-1) && i > (MAX-1)){
//					cout << '*';
//				}else if (i == j){
//					cout << '*';
//				}else{
//				cout << '-';
//				}
//			}
//			cout << '\n';
//			usleep(microseconds);
//		}
//	}
