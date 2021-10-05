#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

const int ROWS = 62;    //total width (divide by 3 for starting width)
const int LPOS = ROWS / 3;
const int RPOS = (ROWS / 3) * 2;
const int COL = 40;     //height
const int MIN_WIDTH = 8;
const int MICROSECONDS = 16000;
enum COLOR{PLAYER = 1, TRAIL, ENEMY, BOOST, SIGN, WALL, WALL2, WALL3}color;
enum INDEX{I_ENEMY, I_TRAIL, I_BOOST, I_LWALL, I_RWALL, I_LSIGN, I_RSIGN}index;

random_device rd;
mt19937 gen(rd());
int rollDie(int low, int high)
{
	uniform_int_distribution<> distr(low, high);
	return distr(rd);
}

class Object
{
public:
	Object()
	{

	}

	void moveObject(vector<Object*> &v)
	{
		for (int i = 0; i < v.size(); i++){
			v[i]->y -= 1;
			if (v[i]->y <= -40){
				v.erase(v.begin()+i);
			}
		}
	}

	bool isThere(vector<Object*> v, int y, int x)
	{
		for (int i = 0; i < v.size(); i++){
			if (v[i]->y == y && v[i]->x == x){
				return true;
			}
		}
		return false;
	}	

	void print(WINDOW *win, char ch, int color, int x, int lpos, int rpos)
	{
		if ((x < lpos || x > rpos) && ch != 'I'){
			waddch(win, ' ');
			return;
		}
		wattron(win, COLOR_PAIR(color));
		waddch(win, ch);
		wattroff(win, COLOR_PAIR(color));
	}

	int x;
	int y;
};

class Trail: public Object
{
public:
	Trail(int i, int j)
	{
		x = i;
		y = j;
	}

	Trail(const Trail &t2)
	{
		x = t2.x;
		y = t2.y;
	}

	~Trail()
	{

	}
};

class Enemy: public Object
{
public:
	Enemy(int rpos, int lpos)
	{
		x = rollDie(lpos+1, rpos-1);
		if (x <= lpos){
			x = lpos + 1;
		}
		y = COL - 1;
	}

	Enemy(const Enemy &e2)
	{
		x = e2.x;
		y = e2.y;
	}
};

class Boost: public Object
{
public:
	Boost(int rpos, int lpos)
	{
		x = rollDie(lpos+3, rpos-3);
		if (x <= lpos){
			x = lpos + 1;
		}
		y = COL - 1;
	}

	Boost(const Boost &b2)
	{
		x = b2.x;
		y = b2.y;
	}
};

class Wall: public Object
{
public:
	Wall(int i, int j)
	{
		x = i;
		y = j;
	}

	Wall(const Wall &w2)
	{
		x = w2.x;
		y = w2.y;
	}

	~Wall()
	{

	}
};

struct Player
{
	int x,y;
	Player()
	{
		x = ROWS / 2;
		y = COL / 2;
	}

	void print(WINDOW *win)
	{
		wattron(win, COLOR_PAIR(PLAYER));
		waddch(win, '*');
		wattroff(win, COLOR_PAIR(PLAYER));
	}
};

void movePlayer(int pos, Player &player, vector<vector<Object*>> Objects, int rpos, int lpos);
void changeSize(int &rpos, int &lpos);
void moveTrack(int &rpos, int &lpos);
void printScreen(WINDOW *win, Player player, vector<vector<Object*>> Objects, Object obj, int timer, int rpos, int lpos, int color);
void enemyCollision(WINDOW *win, Player player, vector<vector<Object*>> Objects, Object obj, bool &gameOver);
bool boostCollision(Player player, vector<vector<Object*>> Objects, Object obj);
bool inRange(int low, int high, int x)
{
	return (x - high) * (x - low) <= 0;
}

void printScreen(WINDOW *win, Player player, vector<vector<Object*>> Objects, Object obj, int timer, int rpos, int lpos, int color)
{
	WINDOW *scoreDisplay = newwin(2, 20, 0, 2);
	mvwprintw(scoreDisplay,1,1, "Score: %d", timer);
	wrefresh(scoreDisplay);
	for (int i = 0; i < COL; i++){
		for (int j = 0; j < ROWS+1; j++){
			if (obj.isThere(Objects[I_LSIGN],i,j) || obj.isThere(Objects[I_RSIGN],i,j)){
				obj.print(win, 'I', SIGN, j, lpos, rpos);
			}
			else if (obj.isThere(Objects[I_LWALL],i,j) || (obj.isThere(Objects[I_RWALL],i,j))){
				obj.print(win, 'I', WALL+color, j, lpos, rpos);
			}
			else if (player.x == j && player.y == i){
				player.print(win);
			}
			else if (obj.isThere(Objects[I_ENEMY],i,j)){
				obj.print(win, 'U', ENEMY, j, lpos, rpos);
			}
			else if (obj.isThere(Objects[I_TRAIL],i,j)){
				int r = TRAIL;
				if (timer % 2 == 0){r = PLAYER;}
				obj.print(win, '|', r, j, lpos, rpos);
			}
			else if (obj.isThere(Objects[I_BOOST],i,j)   ||
			         obj.isThere(Objects[I_BOOST],i,j-1) ||
				 obj.isThere(Objects[I_BOOST],i,j+1)){
				obj.print(win, 'V', BOOST, j, lpos, rpos);
			}
			else{
				waddch(win, ' ');
			}
		}
		wprintw(win, "\n");
	}
	wprintw(win, "\n");
}

int main()
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	WINDOW *win = newwin(COL, ROWS*3, 3, 15);
	scrollok(win, TRUE);
	nodelay(win, TRUE);
	keypad(win, TRUE);
	start_color();
	init_color(COLOR_RED, 700,0,444);
	init_color(COLOR_BLUE, 0,300,888);
	init_color(COLOR_CYAN, 0,888,600);
	init_color(COLOR_YELLOW, 900,888,200);
	init_color(COLOR_WHITE, 700,700,700);
	init_color(COLOR_GREEN, 700, 0, 0);
	init_pair(PLAYER, COLOR_WHITE, COLOR_BLACK);
	init_pair(TRAIL, COLOR_YELLOW, COLOR_BLACK);
	init_pair(ENEMY, COLOR_RED, COLOR_BLACK);
	init_pair(BOOST, COLOR_CYAN, COLOR_BLACK);
	init_pair(SIGN, COLOR_WHITE, COLOR_WHITE);
	init_pair(WALL, COLOR_BLUE, COLOR_BLUE);
	init_pair(WALL2, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(WALL3, COLOR_GREEN, COLOR_GREEN);

	string get = "xset r rate 100 40";
	const char *command = get.c_str();
	system(command);

	int userInput, CONTINUE;
	do{
		int rows = ROWS;
		int lpos = LPOS;
		int rpos = RPOS;
		int microseconds = MICROSECONDS;
		int p_rpos = rpos;
		int p_lpos = lpos;
		int move = 0;            //player direction (-1 = left, 0 = none, 1 = right)
		int enemySpread = 33;    //enemy density (lower = higher)
		int boostSpread = 270;   //boost density (lower = higher)
		int timer = 0;           //game ticks
		int speed = 2;           //enemy speed (lower = faster)
		int r = 0;               //die to roll for random values
		int speedDef = speed;
		bool gameOver = 0;
		int boostDuration = 150;
		int boostDiff;
		int count = 0;
		int color = 0;
		int levelup = 1000;
		vector<vector<Object*>> Objects;
		vector<Object*> enemies, trail, boosts, l_wall, r_wall, l_sign, r_sign;
		Object obj;
		for (int i = 0; i < COLS; i++){
			l_wall.push_back(new Wall(lpos, COL));
			r_wall.push_back(new Wall(rpos, COL));
			Objects.push_back(l_wall);
			Objects.push_back(r_wall);
			obj.moveObject(l_wall);
			obj.moveObject(r_wall);
		}
	
		Player player;
		//main game loop
		do{
			p_rpos = r_wall[50]->x;
			p_lpos = l_wall[50]->x;
			timer++;
			count++;

			if (timer % levelup == true && timer >= levelup){
				enemySpread -= 12;
				if (enemySpread <= 0){
					enemySpread = 8;
				}
				if (color < 2){
					color += 1;
				}
			}

			r = rollDie(0,1);
			//roll to move walls in or out
			if (timer % 8 == 0 && r == 0){
				changeSize(rpos, lpos);
			}
			//roll to move track left or right
			if (timer % 4 == 0 && r == 1){
				moveTrack(rpos, lpos);
			}
			//if boost period is ending, reset speed to normal
			if (boostDiff == timer){
				microseconds = MICROSECONDS;
			}

			//push back objects
			Objects.push_back(enemies);
			Objects.push_back(trail);
			Objects.push_back(boosts);
			Objects.push_back(l_wall);
			Objects.push_back(r_wall);
			Objects.push_back(l_sign);
			Objects.push_back(r_sign);

			//print game state
			printScreen(win, player, Objects, obj, timer, rpos, lpos, color);
			wrefresh(win);

			//get user input and move player
			userInput = wgetch(win);
			switch(userInput)
			{
				case KEY_LEFT:
					move = -1;
					break;
				case KEY_RIGHT:
					move = 1;
					break;
			}
			movePlayer(move, player, Objects, p_rpos, p_lpos);
			move = 0;

			//generate player trail
			trail.push_back(new Trail(player.x, player.y));
			obj.moveObject(trail);

			//generate sign or wall
			if (count == 21){count = 0;}
			if (count < 4){
				l_sign.push_back(new Wall(lpos, COL));
				r_sign.push_back(new Wall(rpos, COL));
			}
			else{
				l_wall.push_back(new Wall(lpos, COL));
				r_wall.push_back(new Wall(rpos, COL));
			}
			obj.moveObject(l_wall);
			obj.moveObject(r_wall);
			obj.moveObject(l_sign);
			obj.moveObject(r_sign);

			//roll to generate enemies
			r  = rollDie(0, enemySpread);
			if (r == enemySpread - 1){
				enemies.push_back(new Enemy(rpos, lpos));
			}
			//roll to generate boosts
			r  = rollDie(0, boostSpread);
			if (r == boostSpread - 1){
				boosts.push_back(new Boost(rpos, lpos));
			}

			//move enemies and boosts
			if (!Objects.empty() && timer % speed == 0){
				obj.moveObject(enemies);
			}
			if (timer % 3 == 0){
				obj.moveObject(boosts);
			}

			//detect collision for enemies
			enemyCollision(win, player, Objects, obj, gameOver);

			//detect collision for boosts and apply boost if valid
			bool isBoost = boostCollision(player, Objects, obj);
			if (isBoost){
				microseconds = microseconds * .6;
				boostDiff = timer + boostDuration;
			}
			Objects.clear();
			usleep(microseconds);        //time between frames
		}while(userInput != 'q' && gameOver == false);

		wclear(win);
		wrefresh(win);
		wprintw(win, "Continue? y/n");
		CONTINUE = wgetch(win);
	}while(userInput != 'q' && CONTINUE != 'n');
	endwin();

	get = "xset r rate 440 22";
	command = get.c_str();
	system(command);

	return 0;
}

void changeSize(int &rpos, int &lpos)
{
	//roll to determine whether to change at all
	int change = rollDie(0, 5);
	if (change != 0){return;}

	//roll to determine to widen or shrink
	change = rollDie(0, 1);
	//widen length
	if (change == 0 && lpos > 0 && rpos < ROWS-1){
		rpos += 1;
		lpos -= 1;
	}
	//shrink length
	else if (change == 1 && rpos <= ROWS && rpos - lpos > MIN_WIDTH){
		rpos -= 1;
		lpos += 1;
	}
}

void moveTrack(int &rpos, int &lpos)
{
	//roll to determine whether to change at all
	int change = rollDie(0, 5);
	if (change != 0){return;}

	//roll to determine left or right movement
	change = rollDie(0, 1);
	//left
	if (change == 0 && lpos > 0){
		rpos -= 1;
		lpos -= 1;
	}
	//right
	else if (change == 1 && rpos < ROWS-1){
		rpos += 1;
		lpos += 1;
	}
}

void movePlayer(int pos, Player &player, vector<vector<Object*>> Objects, int rpos, int lpos)
{
	if (player.x <= lpos){
		player.x += 1;
	}
	if (player.x >= rpos){
		player.x -= 1;
	}
	if (pos == -1){
		player.x -= 1;
	}
	if (pos == 1){
		player.x += 1;
	}
	if (player.x <= lpos){
		player.x += 1;
	}
	if (player.x >= rpos){
		player.x -= 1;
	}
}


void enemyCollision(WINDOW *win, Player player, vector<vector<Object*>> Objects, Object obj, bool &gameOver)
{
	if (obj.isThere(Objects[0], player.y, player.x)){
		fflush(stdout);
		usleep(800000);
		gameOver = true;
	}
}

bool boostCollision(Player player, vector<vector<Object*>> Objects, Object obj)
{
	if (obj.isThere(Objects[2], player.y, player.x)){
		return true;
	}
	if (obj.isThere(Objects[2], player.y, player.x-1)){
		return true;
	}
	if (obj.isThere(Objects[2], player.y, player.x+1)){
		return true;
	}
	return false;
}
