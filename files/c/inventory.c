#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ncurses.h>

#define H_SIZE       84
#define V_SIZE       30
#define START_Y       0
#define START_X       0
#define SPEED_LOW     1
#define SPEED_MED     8
#define SPEED_HIGH   16

#define FIELD_SIZE   20
#define MAXLEN       80

#define LINE_V       '|'
#define LINE_H       '-'
#define CORNER       '+'

int YPOS = 0;

typedef struct category {
  char key;
  char val[80];
} Category;

typedef struct item {
  char name[MAXLEN];
  char model[MAXLEN];
  char categories[MAXLEN];
  char serial[MAXLEN];

  char room[MAXLEN];
  char purchase_date[MAXLEN];

  char comment[MAXLEN];

  char cost[MAXLEN];
  char salvage_value[MAXLEN];
  char lifetime[MAXLEN];
} Item;

Item item_init(char *name, char *model, char *categories, char *serial,
               char *room, char *purchase_date,
               char *comment,
               char *cost, char *salvage_value, char *lifetime)
{
  Item item;

  strcpy(item.name, name);
  strcpy(item.model, model);
  strcpy(item.categories, categories);
  strcpy(item.serial, serial);

  strcpy(item.room, room);
  strcpy(item.purchase_date, purchase_date);

  strcpy(item.comment, comment);

  strcpy(item.cost, cost);
  strcpy(item.salvage_value, salvage_value);
  strcpy(item.lifetime, lifetime);

  return item;
}

enum COLOR { WH_BK, BL_BK, GR_BK, CY_BK, YL_BK } color;

typedef struct rgb {
  unsigned char R, G, B;
} RGB; 

typedef struct screen {
  int height, width;
  int start_y, start_x;
  int color_pair;
  WINDOW *win;
  int field_size;
} Screen;

Screen* screen_init(int height, int width, int start_y, int start_x)
{
  Screen *s = malloc(sizeof(Screen));
  s->start_y = start_y;
  s->start_x = start_x;
  s->height = height;
  s->width = width;
  WINDOW *win = newwin(height, width, start_y, start_x);
  s->win = win;
  YPOS += s->height;
  return s;
}

void draw_win_border(Screen *s)
{
  int i, j;
  char cv = LINE_V;
  char ch = LINE_H;
  char cc = CORNER;

  for (i = 0; i < V_SIZE; i++){
    for (j = 0; j < H_SIZE; j++){
      // Draw corners
      if (i == 0           && j == 0 || i == 0           && j == s->width-1 ||
          i == s->height-1 && j == 0 || i == s->height-1 && j == s->width-1)
        mvwaddch(s->win, i, j, cc);

      else if (i == 0) mvwaddch(s->win, i, j, ch);         /* Top border */
      else if (i == s->height-1) mvwaddch(s->win, i, j, ch);  /* Bottom border */

      else if (j == 0) mvwaddch(s->win, i, j, cv);         /* Left border */
      else if (j == s->width-1) mvwaddch(s->win, i, j, cv);   /* Right border */
    }
  }
}

int print_field(Screen *s, char field[], int field_size, int y, int x)
{
  int i;
  int len = strlen(field);
  mvwaddstr(s->win, y, x, field);
  for (i = x+len; i < field_size+x; i++){
    if (i == s->width-1) break;
    mvwaddch(s->win, y, i, ' ');
  }
  return i;
}

void change_color(Screen *s, int pair)
{
  wattroff(s->win, COLOR_PAIR(s->color_pair));
  wattron(s->win, COLOR_PAIR(pair));
  s->color_pair = pair;
}

void draw_line(Screen *s, int y, char c)
{
  int i;
  for (i = 1; i < s->width-1; i++) mvwaddch(s->win, y, i, c);
}

int print_center(Screen *s, int y, char *str)
{
  int middle = s->width / 2;
  int pos = middle - strlen(str) / 2;
  mvwaddstr(s->win, y, pos, str);
}

int print_right(Screen *s, int y, int offset, char *str)
{
  int right = s->width - offset;
  int pos = right - strlen(str);
  mvwaddstr(s->win, y, pos, str);
}

void draw_header(Screen *s)
{
  change_color(s, CY_BK);
  mvwaddstr(s->win, 0, 0, "INVENTORY MENU");
  change_color(s, YL_BK);
  print_center(s, 0, "PERSONAL INVENTORY");
  change_color(s, CY_BK);
  print_right(s, 0, 0, "SATURDAY 25 APR 15");

  change_color(s, GR_BK);
  mvwaddstr(s->win, 1, 0, "LAST CHANGED 10 SEP 90 at 11:39am");
  print_right(s, 1, 0, "HEADER PAGE");

  change_color(s, YL_BK);
  mvwaddstr(s->win, 2, 0, "INDEX: [item name] Computer XT");
}

void draw_item(Screen *s, Item item)
{
  int i, j;
  int field_size = s->field_size;
  char field[80];
  int len;
  int startX = 2;
  int cursor_posX = startX;

  cursor_posX = print_field(s, "ITEM NAME:", field_size, 1, cursor_posX);
  change_color(s, WH_BK);
  cursor_posX = print_field(s, item.name, field_size, 1, cursor_posX);
  change_color(s, BL_BK);
  cursor_posX = print_field(s, "CATEGORIES:", field_size, 1, cursor_posX);
  change_color(s, WH_BK);
  cursor_posX = print_field(s, item.categories, field_size, 1, cursor_posX);
  change_color(s, BL_BK);

  cursor_posX = startX;
  cursor_posX = print_field(s, "MODEL:", field_size, 2, cursor_posX);
  change_color(s, WH_BK);
  cursor_posX = print_field(s, item.model, field_size, 2, cursor_posX);
  change_color(s, BL_BK);
  cursor_posX = print_field(s, "SERIAL NUMBER:", field_size, 2, cursor_posX);
  change_color(s, WH_BK);
  cursor_posX = print_field(s, item.serial, field_size, 2, cursor_posX);
  change_color(s, BL_BK);


  draw_line(s, 3, LINE_H);
  cursor_posX = startX;
  cursor_posX = print_field(s, "ROOM:", field_size, 4, cursor_posX);
  change_color(s, WH_BK);
  cursor_posX = print_field(s, item.room, field_size, 4, cursor_posX);
  change_color(s, BL_BK);
  cursor_posX = print_field(s, "DATE PURCHASED:", field_size, 4, cursor_posX);
  change_color(s, WH_BK);
  cursor_posX = print_field(s, item.purchase_date, field_size, 4, cursor_posX);
  change_color(s, BL_BK);


  draw_line(s, 5, LINE_H);
  cursor_posX = startX;
  cursor_posX = print_field(s, "COMMENT", field_size, 6, cursor_posX);
  change_color(s, WH_BK);
  cursor_posX = print_field(s, item.comment, field_size*2, 6, cursor_posX);
  change_color(s, BL_BK);


  draw_line(s, 7, LINE_H);
  cursor_posX = startX;
  cursor_posX = print_field(s, "COST:", field_size, 8, cursor_posX);
  change_color(s, WH_BK);
  cursor_posX = print_field(s, item.cost, field_size, 8, cursor_posX);
  change_color(s, BL_BK);
  cursor_posX = print_field(s, "SALVAGE VALUE:", field_size, 8, cursor_posX);
  change_color(s, WH_BK);
  cursor_posX = print_field(s, item.salvage_value, field_size, 8, cursor_posX);
  change_color(s, BL_BK);

  cursor_posX = startX;
  cursor_posX = print_field(s, "LIFETIME:", field_size, 9, cursor_posX);
  change_color(s, WH_BK);
  cursor_posX = print_field(s, item.lifetime, field_size, 9, cursor_posX);
  change_color(s, BL_BK);


  draw_line(s, 10, LINE_H);
}

void draw_categories(Screen *s, Category categories[], int num_categories)
{
  int i;
  int startX = 3;
  int cursor_posX = startX;
  int index = 0;

  // Draw header
  change_color(s, YL_BK);
  print_center(s, 0, "CATEGORIES");
  change_color(s, BL_BK);

  // Draw categories
  while (index < num_categories){
    for (i = 1; i < s->height-1; i++){
      if (index >= num_categories) goto done;
      mvwaddch(s->win, i, cursor_posX, categories[index].key);
      mvwaddstr(s->win, i, cursor_posX+2, categories[index].val);
      index++;
    }
    cursor_posX += s->field_size;
  }

done:
  return;
}

void get_colors_default()
{
  init_color(COLOR_RED,    219,  34,  34);
  init_color(COLOR_BLUE,    52,  91, 133);
  init_color(COLOR_CYAN,    29, 199, 252);
  init_color(COLOR_YELLOW, 255, 255,  85);
  init_color(COLOR_WHITE,  255, 255, 255);
  init_color(COLOR_GREEN,   64, 255,  83);
  init_color(COLOR_BLACK,   31,  37,  32);
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
  init_pair(YL_BK, COLOR_YELLOW, COLOR_BLACK);

  int i, j;
  char input;

  // Initialize header screen
  Screen *s_header = screen_init(3, H_SIZE, YPOS, START_X);

  // Initialize item screen
  Screen *s_item = screen_init(11, H_SIZE, YPOS, START_X);
  s_item->field_size = 20;

  // Initialize categories screen
  Screen *s_categories = screen_init(8, H_SIZE, YPOS, START_X);
  s_categories->field_size = 23;
  nodelay(s_item->win, TRUE);
  keypad(s_item->win, TRUE);

  // Example item
  Item item = item_init("Computer XT", "Generic", "AC", "9382 9943 4324 32223",
                        "study", "21 Feb 89",
                        "Includes 1 year warranty",
                        "$2,500.00", "$500.00", "5 years");

  // Categories
  Category appliances; appliances.key = 'A'; strcpy(appliances.val, "Appliances");
  Category automotive; automotive.key = 'B'; strcpy(automotive.val, "Automotive tool");
  Category sporting;   sporting.key   = 'C'; strcpy(sporting.val,   "Sporting Equip");
  Category software;   software.key   = 'D'; strcpy(software.val,   "Computer Swr");
  Category hardware;   hardware.key   = 'E'; strcpy(hardware.val,   "Computer Hwr");
  Category jewelry;    jewelry.key    = 'F'; strcpy(jewelry.val,    "Jewelry");
  Category gardening;  gardening.key  = 'G'; strcpy(gardening.val,  "Gardening Equip");
  Category warranty;   warranty.key   = 'W'; strcpy(warranty.val,   "Warranty");
  Category nowarranty; nowarranty.key = 'X'; strcpy(nowarranty.val, "NO Warranty");
  int num_categories = 9;
  Category categories[num_categories];
  categories[0] = appliances;
  categories[1] = automotive;
  categories[2] = sporting;
  categories[3] = software;
  categories[4] = hardware;
  categories[5] = jewelry;
  categories[6] = gardening;
  categories[7] = warranty;
  categories[8] = nowarranty;

  change_color(s_categories, BL_BK);
  draw_win_border(s_categories);

  do{
    // Draw header screen
    draw_header(s_header);
    wrefresh(s_header->win);

    // Draw item screen
    change_color(s_item, BL_BK);
    draw_win_border(s_item);
    draw_item(s_item, item);
    wrefresh(s_item->win);

    // Draw categories screen
    change_color(s_categories, BL_BK);
    draw_categories(s_categories, categories, num_categories);
    wrefresh(s_categories->win);
  } while (input != 'q');

  /* Exit */
  endwin();
  
  return 0;
}
