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

void draw_header(ACscreen *s)
{
  ac_changeColor(s, CY_BK);
  mvwaddstr(s->win, 0, 0, "INVENTORY MENU");
  ac_changeColor(s, YL_BK);
  ac_printCenter(s, 0, "PERSONAL INVENTORY");
  ac_changeColor(s, CY_BK);
  ac_printRight(s, 0, "SATURDAY 25 APR 15", 0);

  ac_changeColor(s, GR_BK);
  mvwaddstr(s->win, 1, 0, "LAST CHANGED 10 SEP 90 at 11:39am");
  ac_printRight(s, 1, "HEADER PAGE", 0);

  ac_changeColor(s, YL_BK);
  mvwaddstr(s->win, 2, 0, "INDEX: [item name] Computer XT");
}

void draw_item(ACscreen *s, Item item)
{
  int i, j;
  int field_size = s->field_size;
  char field[80];
  int len;
  int startX = 2;
  int cursor_posX = startX;

  ac_printField(s, 1, cursor_posX, field_size, "ITEM NAME:");
  ac_changeColor(s, WH_BK);
  ac_printField(s, 1, cursor_posX += field_size, field_size, item.name);
  ac_changeColor(s, BL_BK);
  ac_printField(s, 1, cursor_posX += field_size, field_size, "CATEGORIES");
  ac_changeColor(s, WH_BK);
  ac_printField(s, 1, cursor_posX += field_size, field_size, item.categories);
  ac_changeColor(s, BL_BK);

  cursor_posX = startX;
  ac_printField(s, 2, cursor_posX, field_size, "MODEL:");
  ac_changeColor(s, WH_BK);
  ac_printField(s, 2, cursor_posX += field_size, field_size, item.model);
  ac_changeColor(s, BL_BK);
  ac_printField(s, 2, cursor_posX += field_size, field_size, "SERIAL NUMBER:");
  ac_changeColor(s, WH_BK);
  ac_printField(s, 2, cursor_posX += field_size, field_size, item.serial);
  ac_changeColor(s, BL_BK);


  ac_drawLineH(s, 3, LINE_H, 0);
  cursor_posX = startX;
  ac_printField(s, 4, cursor_posX, field_size, "ROOM:");
  ac_changeColor(s, WH_BK);
  ac_printField(s, 4, cursor_posX += field_size, field_size, item.room);
  ac_changeColor(s, BL_BK);
  ac_printField(s, 4, cursor_posX += field_size, field_size, "DATE PURCHASED:");
  ac_changeColor(s, WH_BK);
  ac_printField(s, 4, cursor_posX += field_size, field_size, item.purchase_date);
  ac_changeColor(s, BL_BK);


  ac_drawLineH(s, 5, LINE_H, 0);
  cursor_posX = startX;
  ac_printField(s, 6, cursor_posX, field_size, "COMMENT");
  ac_changeColor(s, WH_BK);
  ac_printField(s, 6, cursor_posX += field_size, field_size*2, item.comment);
  ac_changeColor(s, BL_BK);


  ac_drawLineH(s, 7, LINE_H, 0);
  cursor_posX = startX;
  ac_printField(s, 8, cursor_posX, field_size, "COST:");
  ac_changeColor(s, WH_BK);
  ac_printField(s, 8, cursor_posX += field_size, field_size, item.cost);
  ac_changeColor(s, BL_BK);
  ac_printField(s, 8, cursor_posX += field_size, field_size, "SALVAGE VALUE:");
  ac_changeColor(s, WH_BK);
  ac_printField(s, 8, cursor_posX += field_size, field_size, item.salvage_value);
  ac_changeColor(s, BL_BK);

  cursor_posX = startX;
  ac_printField(s, 9, cursor_posX, field_size, "LIFETIME:");
  ac_changeColor(s, WH_BK);
  ac_printField(s, 9, cursor_posX += field_size, field_size, item.lifetime);
  ac_changeColor(s, BL_BK);


  ac_drawLineH(s, 10, LINE_H, 0);
}

void draw_categories(ACscreen *s, Category categories[], int num_categories)
{
  int i;
  int startX = 3;
  int cursor_posX = startX;
  int index = 0;

  // Draw header
  ac_changeColor(s, YL_BK);
  ac_printCenter(s, 0, "CATEGORIES");
  ac_changeColor(s, BL_BK);

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

int main()
{
  ac_init(0, 0);
  ac_colorStart();

  // Initialize header screen
  ACscreen *s_header = ac_screenInit(3, H_SIZE, AC_YPOS, START_X);

  // Initialize item screen
  ACscreen *s_item = ac_screenInit(11, H_SIZE, AC_YPOS, START_X);
  s_item->field_size = 20;
  nodelay(s_item->win, TRUE);
  keypad(s_item->win, TRUE);

  // Initialize categories screen
  ACscreen *s_categories = ac_screenInit(8, H_SIZE, AC_YPOS, START_X);
  s_categories->field_size = 23;

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

  ac_changeColor(s_categories, BL_BK);
  ac_drawBorder(s_categories);

  char input;
  do{
    // Draw header screen
    draw_header(s_header);
    wrefresh(s_header->win);

    // Draw item screen
    ac_changeColor(s_item, BL_BK);
    ac_drawBorder(s_item);
    draw_item(s_item, item);
    wrefresh(s_item->win);

    // Draw categories screen
    ac_changeColor(s_categories, BL_BK);
    draw_categories(s_categories, categories, num_categories);
    wrefresh(s_categories->win);
  } while (input != 'q');

  ac_close();
}
