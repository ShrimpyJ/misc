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
#define SLIDER_LEN   10
#define SLIDER_WIDTH  7

#define SPEED_FAST   16
#define SPEED_MID     4
#define SPEED_SLOW    1

#define INFO_COLOR "WH_BK"


void draw_header(ACscreen *s)
{
  ac_changeColor(s, BL_BK); ac_printCenter(s, 0, "COLOR PICKER");

  wrefresh(s->win);
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

  // Draw border if border=1
  if (s->border){
    ac_changeColor(s->parent, s->color_border);

    // top bar
    for (i = 0; i < s->length+2; i++){
      if (i == 0 || i == s->length+1) mvwaddch(s->parent->win, ypos, xpos+i, s->c);
      else mvwaddch(s->parent->win, ypos, xpos+i, s->h);
    }
  
    // bottom bar
    for (i = 0; i < s->length+2; i++){
      if (i == 0 || i == s->length+1) mvwaddch(s->parent->win, ypos+2, xpos+i, s->c);
      else mvwaddch(s->parent->win, ypos+2, xpos+i, s->h);
    }
  
    // side bars
    mvwaddch(s->parent->win, ypos+1, xpos, s->v);
    mvwaddch(s->parent->win, ypos+1, xpos+s->length+1, s->v);
  }
  else{  // Undo border offsets if no border before drawing middle bar
    ypos--;
    xpos--;
  }

  // middle bar
  ac_changeColor(s->parent, s->color_fill);
  int size = map(s->val, s->min, s->max, 0, s->length);
  for (i = 0; i < s->length; i++){
    mvwaddch(s->parent->win, ypos+1, xpos+i+1, s->empty);
  }
  for (i = 0; i < size; i++){
    mvwaddch(s->parent->win, ypos+1, xpos+i+1, s->fill);
  }

  // Undo border offsets if no border before drawing label
  if (!s->border){
    ypos--;
    xpos++;
  }

  // label
  ac_changeColor(s->parent, s->color_label);
  if (s->label[0] != '\0'){
    mvwaddstr(s->parent->win, ypos+3, xpos, s->label);
    mvwaddstr(s->parent->win, ypos+3, xpos+strlen(s->label), "   ");
    wmove(s->parent->win, ypos+3, xpos+strlen(s->label));
    wprintw(s->parent->win, "%d", s->val);
  }

  // val
  ac_changeColor(s->parent, s->color_val);

  wrefresh(s->parent->win);
}

void draw_main(ACscreen *screen, Slider *RGB[])
{
  int i;

  // sliders
  for (i = 0; i < 3; i++){
    Slider *slider = RGB[i];
    ac_sliderDraw(slider);
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

void construct_slider(Slider *s, int y, int x, char *label, int color_all, int print_val)
{
  s->start_y = y;
  s->start_x = x;
  strcpy(s->label, label);
  ac_sliderColorAll(s, color_all);
  s->print_val = print_val;
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
  ACscreen *sInfo = ac_screenInit(5, H_SIZE, AC_YPOS-1, START_X);
  ac_drawBorder(sInfo);

  // Initialize image screen
  ACscreen *sImage = ac_screenInit(sMain->height*0.75, sMain->width*0.5,
                                   sMain->end_yRel*0.25, sMain->end_xRel*0.05);
  ac_drawBorder(sImage);

  // Create color sliders
  int bar_offset = SLIDER_WIDTH+3;
  Slider *red = ac_sliderInit(sMain, 0, 255, SLIDER_LEN, SLIDER_WIDTH);
  int tmpX = red->parent->end_xRel*.60;
  int tmpY = red->parent->end_yRel*.15;
  construct_slider(red, tmpY, tmpX, "R: ", RD_BK, 1);
  red->isHorizontal = 0;

  Slider *green = ac_sliderInit(sMain, 0, 255, SLIDER_LEN, SLIDER_WIDTH);
  tmpX = red->start_x+bar_offset;
  tmpY = red->start_y;
  construct_slider(green, tmpY, tmpX, "G: ", GR_BK, 1);
  green->isHorizontal = 0;

  Slider *blue = ac_sliderInit(sMain, 0, 255, SLIDER_LEN, SLIDER_WIDTH);
  tmpX = green->start_x+bar_offset;
  tmpY = green->start_y;
  construct_slider(blue, tmpY, tmpX, "B: ", BL_BK, 1);
  blue->isHorizontal = 0;

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

  ac_end();
}
