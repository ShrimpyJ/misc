#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "acurses.h"

#define BUFSIZE 100

typedef struct line{
  char *data;
  int id;
  int len;
} Line;

FILE *open_file(const char *name)
{
  FILE *fp;
  if ((fp = fopen(name, "r+")) == NULL ){
    fprintf(stderr, "error: could not open %s\n", name);
    exit(1);
  }
  return fp;
}

void print_file(ACscreen *s, FILE *fp, int curs_y, int curs_x)
{
  char buf[2];
  int ypos, xpos;
  memset(buf, 0, 2);
  ypos = xpos = 0;
  while (fread(buf, 1, 1, fp) > 0){
    mvwaddch(s->win, ypos, xpos++, buf[0]);
    if (buf[0] == '\n'){
      ypos++;
      xpos = 0;
    }
    memset(buf, 0, 2);
  }
  wmove(s->win, curs_y, curs_x);
}

Line **read_file(FILE *fp, int *nl)
{
  int num_lines = 0;
  char buf[2];

  // Read once to get # of lines
  while (fread(buf, 1, 1, fp) > 0){
    if (buf[0] == '\n') num_lines++;
  }

  fseek(fp, 0, SEEK_SET);

  Line **lines = calloc(num_lines, sizeof(Line *));

  // Read again to get length of each line
  int i = 0;
  int len = 0;
  while (fread(buf, 1, 1, fp) > 0){
    len++;
    if (buf[0] == '\n'){
      lines[i] = calloc(1, sizeof(Line));
      lines[i]->len = len;
      lines[i]->data = calloc(len+1, sizeof(char));
      lines[i]->id = i;
      len = 0;
      i++;
    }
  }

  fseek(fp, 0, SEEK_SET);

  // Read data into lines
  i = 0;
  int j = 0;
  while (fread(buf, 1, 1, fp) > 0){
    j++;
    lines[i]->data[j] = buf[0];
    if (buf[0] == '\n'){
      i++;
      j = 0;
    }
  }

  *nl = num_lines;

  return lines;
}

int main(int argc, char **argv)
{
  FILE *fp;
  int ch;
  int curs_y, curs_x;
  int num_lines;
  int i;

  if (argc != 2){
    fprintf(stderr, "usage: brutus FILE\n");
    exit(1);
  }

  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  nodelay(stdscr, 1);
  ac_colorStart();

  ACscreen *sMain = ac_screenInit(40, 80, 0, 0);
  ac_unsetBorder(sMain);

  fp = open_file(argv[1]); 
  Line **lines = read_file(fp, &num_lines);

  fseek(fp, 0, SEEK_SET);

  curs_y = curs_x = 0;
  for (i = 0; i < num_lines; i++){
    wprintw(sMain->win, "%s", lines[i]);
  }

  print_file(sMain, fp, curs_y, curs_x);

  int end = 0;
  do{
    refresh();
    end = lines[curs_y]->len-2;
    switch(ch){
      case 'h': curs_x--; break;
      case 'l': curs_x++; break;
      case 'j': curs_y++; break;
      case 'k': curs_y--; break;
      case '$': curs_x = end; break;
      case '0': curs_x = 0; break;
    }
    if (curs_x > end && curs_x > 0) curs_x = end;
    if (curs_y < 0) curs_y = 0;
    if (curs_x < 0) curs_x = 0;
    if (curs_y > num_lines-1) curs_y = num_lines-1;
    wmove(sMain->win, curs_y, curs_x);
    ac_refresh(sMain);

//    print_file(sMain, fp, curs_y, curs_x);

  } while((ch = wgetch(sMain->win)));

  fclose(fp);
  endwin();
}
