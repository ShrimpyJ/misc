#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "acurses.h"

#define H_SIZE       84
#define V_SIZE       30
#define START_Y       0
#define START_X       0

#define FIELD_SIZE   20
#define MAXLEN       80
#define SLIDER_LEN   24

#define SPEED_FAST   16
#define SPEED_MID     4
#define SPEED_SLOW    1

#define INFO_COLOR "WH_BK"

typedef struct slider {
  ACscreen *parent;
  int val;
  int min;
  int max;
  int length;
  int wrap;
  int horizontal;
  int start_y;
  int start_x;
  char label[80];
  int color;
} Slider;

const char* IMAGE =
"      ------\n\
      |    |\n\
           |\n\
           |\n\
           |\n\
           |\n\
           |\n\
           |\n\
    ========\n";

void draw_header(ACscreen *s)
{
  ac_changeColor(s, BL_BK); ac_printCenter(s, 0, "COLOR PICKER");

  wrefresh(s->win);
}

Slider *slider_init(ACscreen *parent, int min, int max, int length, int wrap, int horizontal)
{
  Slider *s = calloc(1, sizeof(Slider));;
  s->parent = parent;
  s->val = 0;
  s->min = min;
  s->max = max;
  s->length = length;
  if (wrap == 0) s->wrap = 0;
  else s->wrap = 1;
  if (horizontal == 0) s->horizontal = 0;
  else s->horizontal = 1;
  return s;
}

int map(int val, int A, int B, int a, int b)
{
  return (val - A) * (b - a) / (B - A) + a;
}

void draw_slider(Slider *s)
{
  int i;
  int ypos = s->start_y;
  int xpos = s->start_x;

  // top bar
  for (i = 0; i < s->length+2; i++){
    if (i == 0 || i == s->length+1) mvwaddch(s->parent->win, ypos, xpos+i, '+');
    else mvwaddch(s->parent->win, ypos, xpos+i, '-');
  }

  // bottom bar
  for (i = 0; i < s->length+2; i++){
    if (i == 0 || i == s->length+1) mvwaddch(s->parent->win, ypos+2, xpos+i, '+');
    else mvwaddch(s->parent->win, ypos+2, xpos+i, '-');
  }

  // side bars
  mvwaddch(s->parent->win, ypos+1, xpos, '|');
  mvwaddch(s->parent->win, ypos+1, xpos+s->length+1, '|');

  // middle bar
  int size = map(s->val, s->min, s->max, 0, s->length);
  for (i = 0; i < s->length; i++){
    mvwaddch(s->parent->win, ypos+1, xpos+i+1, ' ');
  }
  for (i = 0; i < size; i++){
    mvwaddch(s->parent->win, ypos+1, xpos+i+1, '=');
  }

  // label
  mvwaddstr(s->parent->win, ypos+3, xpos, s->label);
  mvwaddstr(s->parent->win, ypos+3, xpos+strlen(s->label), "   ");
  wmove(s->parent->win, ypos+3, xpos+strlen(s->label));
  wprintw(s->parent->win, "%d", s->val);

  wrefresh(s->parent->win);
}

void draw_main(ACscreen *screen, Slider *RGB[])
{
  int i;

  // sliders
  for (i = 0; i < 3; i++){
    Slider *slider = RGB[i];
    ac_changeColor(screen, slider->color);
    draw_slider(slider);
    wrefresh(screen->win);
  }

  ACscreen *sHeader = ac_screenInit(3, H_SIZE, AC_YPOS, START_X);

  // image
  wrefresh(screen->win);
}

void draw_info(ACscreen *s, int speed, char ch)
{
  // Speed
  if (speed == SPEED_SLOW) ac_changeColor(s, YL_BK);
  mvwaddstr(s->win, s->start_yRel+1, s->start_xRel+2, "1: SPEED SLOW");
  ac_changeColor(s, WH_BK);
  if (speed == SPEED_MID) ac_changeColor(s, YL_BK);
  mvwaddstr(s->win, s->start_yRel+2, s->start_xRel+2, "2: SPEED MEDIUM");
  ac_changeColor(s, WH_BK);
  if (speed == SPEED_FAST) ac_changeColor(s, YL_BK);
  mvwaddstr(s->win, s->start_yRel+3, s->start_xRel+2, "3: SPEED FAST");
  ac_changeColor(s, WH_BK);

  // Colors
  if (ch == 'y' || ch == 'u') ac_changeColor(s, RD_BK);
  mvwaddstr(s->win, s->start_yRel+1, s->end_xRel*.33, "Y: Decrease Red");
  mvwaddstr(s->win, s->start_yRel+1, s->end_xRel*.66, "U: Increase Red");
  mvwaddstr(s->win, s->start_yRel+2, s->end_xRel*.33, "H: Decrease Green");
  mvwaddstr(s->win, s->start_yRel+2, s->end_xRel*.66, "J: Increase Green");
  mvwaddstr(s->win, s->start_yRel+3, s->end_xRel*.33, "N: Decrease Blue");
  mvwaddstr(s->win, s->start_yRel+3, s->end_xRel*.66, "M: Increase Blue");

  wrefresh(s->win);
}

void draw_image(ACscreen *s, Slider *RGB[])
{
  init_color(COLOR_MAGENTA, RGB[0]->val, RGB[1]->val, RGB[2]->val);
  ac_changeColor(s, MG_BK);
  refresh();
  wrefresh(s->win);
  ac_printCenter(s, 0, "MERRY CHRISTMAS");
  ac_printCenter(s, 2, "*");
  ac_printCenter(s, 3, "XXX");
  ac_printCenter(s, 4, "XXXXXXX");
  ac_printCenter(s, 5, "XXXXXXXXX");
  ac_printCenter(s, 6, "XXXXXXX");
  ac_printCenter(s, 7, "XXXXXXXXXXX");
  ac_printCenter(s, 8, "XXXXXXXXXXXXXXX");
  ac_printCenter(s, 9, "XXXXXXXXXXXXXXXXXXX");
  ac_printCenter(s, 10, "XXXXXXXXXXXXXXX");
  ac_printCenter(s, 11, "XXXXXXXXXXXXXXXXXXX");
  ac_printCenter(s, 12, "XXXXXXXXXXXXXXXXXXXXX");
  ac_printCenter(s, 13, "XXXXXXXXXXXXXXXXX");
  ac_printCenter(s, 14, "XXXXXXXXXXX");
  ac_printCenter(s, 14, "XXXXXXXXX");
  ac_printCenter(s, 15, "#####");
  ac_printCenter(s, 16, "#####");
  ac_printCenter(s, 17, "#####");
  ac_printCenter(s, 18, "         _*_    #####           __*__");
  ac_printCenter(s, 19, "         |_|            -*-     |   |");
  ac_printCenter(s, 20, "                        |_|     |___|");
  wrefresh(s->win);
}

int main()
{
  ac_init(0, 0);
  ac_colorStart();

  // Initialize header screen
  ACscreen *sHeader = ac_screenInit(3, H_SIZE, AC_YPOS, START_X);
  ac_changeColor(sHeader, GR_BK);

  // Initialize main screen
  ACscreen *sMain = ac_screenInit(30, H_SIZE, AC_YPOS, START_X);
  ac_drawBorder(sMain);

  // Initialize info screen
  ACscreen *sInfo = ac_screenInit(5, H_SIZE, sMain->end_y, START_X);
  ac_drawBorder(sInfo);

  // Initialize image screen
  ACscreen *sImage = ac_screenInit(sMain->height*0.75, sMain->width*0.5,
                                   sMain->end_yRel*0.25, sMain->end_xRel*0.05);
  ac_drawBorder(sImage);

  // Create color sliders
  int bar_offset = 5;
  Slider *red = slider_init(sMain, 0, 255, SLIDER_LEN, 0, 1);
  red->start_x = red->parent->end_xRel*.66;
  red->start_y = red->parent->end_yRel*.15;
  strcpy(red->label, "R: ");
  red->color = RD_BK;
  Slider *green = slider_init(sMain, 0, 255, SLIDER_LEN, 0, 1);
  green->start_x = red->start_x;
  green->start_y = red->start_y+bar_offset;
  green->color = GR_BK;
  strcpy(green->label, "G: ");
  Slider *blue = slider_init(sMain, 0, 255, SLIDER_LEN, 0, 1);
  blue->start_x = green->start_x;
  blue->start_y = green->start_y+bar_offset;
  blue->color = BL_BK;
  strcpy(blue->label, "B: ");

  Slider *RGB[3];
  RGB[0] = red;
  RGB[1] = green;
  RGB[2] = blue;

  nodelay(stdscr, 1);
  char ch;
  int speed = SPEED_SLOW;
  int i;
  do{
    attron(A_BOLD);
    refresh();

    // Input and logic
    switch(ch){
      case '1': speed = SPEED_SLOW; break;
      case '2': speed = SPEED_MID; break;
      case '3': speed = SPEED_FAST; break;
      case 'y': red->val -= speed; break;
      case 'u': red->val += speed; break;
      case 'h': green->val -= speed; break;
      case 'j': green->val += speed; break;
      case 'n': blue->val -= speed; break;
      case 'm': blue->val += speed; break;
    }
    for (i = 0; i < 3; i++){
      if (RGB[i]->val > RGB[i]->max) RGB[i]->val = RGB[i]->max;
      if (RGB[i]->val < 0)           RGB[i]->val = 0;
    }

    // Header
    draw_header(sHeader);

    // Main
    draw_main(sMain, RGB);

    // Info
    draw_info(sInfo, speed, ch);

    // Image
    draw_image(sImage, RGB);
  } while ((ch = getch()) != 'q');

  ac_close();
}
