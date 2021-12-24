#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ncurses.h>

#define H_SIZE       80
#define V_SIZE       30
#define START_Y       5
#define START_X      20
#define SPEED_LOW     1
#define SPEED_MED     8
#define SPEED_HIGH   16

enum COLOR { WH_BK, BL_BK, GR_BK, CY_BK } color;

typedef struct rgb {
  unsigned char R, G, B;
} RGB; 

typedef struct screen {
  int height, width;
  int start_y, start_x;
  unsigned char R, G, B;
} Screen;

WINDOW* screen_init(Screen *s, int height, int width, int start_y, int start_x)
{
  s = malloc(sizeof(Screen));
  s->start_y = start_y;
  s->start_x = start_x;
  s->height = height;
  s->width = width;
  WINDOW *win = newwin(height, width, start_y, start_x);
  return win;
}

void draw_win_border(WINDOW *win, int height, int width)
{
  int i, j;
  char c;
  c = '0';

  for (i = 0; i < V_SIZE; i++){
    for (j = 0; j < H_SIZE; j++){
      if (i == 0) mvwaddch(win, i, j, c);         /* Top border */
      if (i == height-1) mvwaddch(win, i, j, c);  /* Bottom border */

      if (j == 0) mvwaddch(win, i, j, c);         /* Left border */
      if (j == width-1) mvwaddch(win, i, j, c);   /* Right border */
    }
  }
}

void get_colors_default()
{
  init_color(COLOR_RED,    219,  34,  34);
  init_color(COLOR_BLUE,    52,  91, 133);
  init_color(COLOR_CYAN,    29, 199, 252);
  init_color(COLOR_YELLOW, 222, 211,  60);
  init_color(COLOR_WHITE,  255, 255, 255);
  init_color(COLOR_GREEN,   64, 255,  83);
  init_color(COLOR_BLACK,   31,  37,  32);
}

void change_color(char c, int color, RGB *set, int n)
{
  switch(c)
  {
    case 'q':
      set->R -= n; break;
    case 'w':
      set->R += n; break;
    case 'a':
      set->G -= n; break;
    case 's':
      set->G += n; break;
    case 'z':
      set->B -= n; break;
    case 'x':
      set->B += n; break;
  }
  init_color(color, set->R, set->G, set->B);
}

int align_center(int len)
{
  return H_SIZE / 2 - len / 2 - 1;
}

void draw_banner(WINDOW *win)
{
  char *title;
  title = "Color Selector\0";
  mvwprintw(win, 0, align_center(strlen(title)), title);
}

int main(int argc, char** argv)
{
  /* ncurses basic setup */
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
//  WINDOW *win = newwin(V_SIZE, H_SIZE, 1, 1);
//  scrollok(win, TRUE);
  clear();

  /* ncurses color setup */
  start_color();
  get_colors_default();
  init_pair(WH_BK, COLOR_WHITE, COLOR_BLACK);
  init_pair(BL_BK, COLOR_BLUE, COLOR_BLACK);
  init_pair(GR_BK, COLOR_GREEN, COLOR_BLACK);
  init_pair(CY_BK, COLOR_CYAN, COLOR_BLACK);

  int i, j;
  char input;
  RGB *set;
  set = malloc(sizeof(RGB));
  set->R = 129;
  set->G = 199;
  set->B = 252;

  Screen *screen_main;
  WINDOW *win = screen_init(screen_main, V_SIZE, H_SIZE, START_Y, START_X);
  nodelay(win, TRUE);
  keypad(win, TRUE);

  do{
    wattron(win, COLOR_PAIR(BL_BK));
//    draw_banner(win);
    input = wgetch(win);
    change_color(input, COLOR_BLUE, set, SPEED_LOW);
    draw_win_border(win, V_SIZE, H_SIZE);
    wrefresh(win);
  } while (input != 'p');

  /* Exit */
  endwin();
  
  return 0;
}
