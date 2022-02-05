#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <locale.h>
#include "acurses.h"

int AC_YPOS = 0;   // Tracks ypos of bottommost screen

// Rounds up if an odd length
int get_middle(int len)
{
  if (len % 2 == 0) return len / 2;
  else return len / 2 + 1;
}

////////////////////// Screen ///////////////////////////////
// Initialize a new screen with relevant info.
// Pass AC_YPOS in place of start_y to have
// the new window be placed directly below
// the most recently created window.
// You can use any existing window's start, mid, and end values
// to spawn new windows next to or inside of them.
ACscreen *ac_screenInit(int height, int width, int start_y, int start_x)
{
  ACscreen *s = malloc(sizeof(ACscreen));

  s->height = height;
  s->width = width;

  // Positions relative to the entire program (stdscr)
  s->start_y = start_y;
  s->start_x = start_x;
  s->end_y = s->start_y + s->height;
  s->end_x = s->start_x + s->width;
  s->mid_y = get_middle(s->end_y);
  s->mid_x = get_middle(s->end_x);

  // Positions relative to the window only
  s->start_yRel = 0;
  s->start_xRel = 0;
  s->end_yRel = s->height-1;
  s->end_xRel = s->width-1;
  s->mid_yRel = s->start_y + s->mid_y;
  s->mid_xRel = s->start_x + s->mid_x;
  s->mid_xRel = get_middle(s->width);

  s->win = newwin(height, width, start_y, start_x);
  if (start_y >= AC_YPOS) AC_YPOS += s->height;
  s->color = WH_BK;

  // Set default title settings
  s->title[0] = '\0';
  s->title_color = WH_BK;
  s->title_pos = CENTER;
  s->title_offset = 0;

  // Set default border settings
  s->has_border = 1;
  s->border_color = WH_BK;
  s->border_offset = 2;

  // Set default highlight settings
  s->hl_color = BK_WH;
  s->hl_line = 1;      // Set to 1 to highlight entire screen minus border
  s->hl_forward = 0;   // Constant. Set to always highlight n spaces forward
  s->hl_backward = 0;  // Constant. Set to always highlight n spaces backward


  // Set default settings for a menu
  // Menus are syntactic sugar for screens
  s->nitems = 0;
  s->items = calloc(1, sizeof(char *));
  s->cur_item = 0;              // Currently highlighted item
  s->item_start_x = 1;   // Starting position of items list
  s->item_start_y = 1;   // Starting position of items list
  s->top_visible = 0;    // Track the top and bottom
  s->bot_visible = 0;    // visible items for scrolling
  s->wrap = 1;           // Set to 1 to allow menu to wrap back around
  s->scrolloff = 1;      // Set to view more lines before scrolling

  return s;
}

// Changes the color pair stored in a screen and updates the window
// Pass in an enum pair such as BL_BK for blue text on black background
void ac_changeColor(ACscreen *s, int pair)
{
  wattroff(s->win, COLOR_PAIR(s->color));
  wattron(s->win, COLOR_PAIR(pair));
}

// Set all title settings. pos can be LEFT, CENTER/MIDDLE, or RIGHT.
// Offset only applies to LEFT or RIGHT.
void ac_setTitle(ACscreen *s, char *name, int color, int pos, int offset)
{
  memset(s->title, 0, CMAX);
  strncpy(s->title, name, strlen(name));
  s->title_color = color;
  s->title_pos = pos;
  s->title_offset = offset;
}

// Erase a title. Calls to ac_drawTitle() will
// instantly return if no title exists.
void ac_unsetTitle(ACscreen *s)
{
  memset(s->title, 0, CMAX);
}

// Unset a border. Calls to ac_drawBorder() will
// instantly return if no border exists.
void ac_unsetBorder(ACscreen *s)
{
  s->has_border = 0;
  s->border_offset = 1;
}

// Draw screen title in center of screen's top row.
// Overlaps the top border by default if border is set.
// Will return if no title is set.
void ac_drawTitle(ACscreen *s)
{
  if (s->title[0] == '\0') return;
  ac_changeColor(s, s->title_color);
  if (s->title_pos == LEFT) mvwaddstr(s->win, 0, 0+s->title_offset, s->title);
  else if (s->title_pos == CENTER) ac_printCenter(s, 0, s->title);
  else ac_printRight(s, 0, s->title, s->title_offset);
  ac_changeColor(s, s->color);
}

// Draws a default curses border set to the screen's color.
// For custom ASCII borders, use ac_drawBorderCh()
void ac_drawBorder(ACscreen *s)
{
  if (!s->has_border) return;
  ac_changeColor(s, s->border_color);
  wborder(s->win, 0, 0, 0, 0, 0, 0, 0, 0);
  ac_changeColor(s, s->color);
}

/*
  Draws a custom border on the outer edges of the screen's window.
  Border characters are the defaults defined in the header file.
  A screen must have has_border set for the border to be draw.
  It is set by default and can be unset with ac_unsetBorder().

  Example of a default border for an 8x5 window:
  +------+
  |      |
  |      |
  |      |
  +------+

  Drawing a border is nice but also requires some attention when drawing
  text to avoid colliding with it. Pay attention to offsets.
*/
void ac_drawBorderCh(ACscreen *s)
{
  int i, j;
  int h = s->h;
  int v = s->v;
  int tl = s->tl;
  int tr = s->tr;
  int bl = s->bl;
  int br = s->br;

  if (!s->has_border) return;

  for (i = 0; i < s->height; i++){
    for (j = 0; j < s->width; j++){
      // Draw corners
      if      (i == 0 && j == 0) mvwaddch(s->win, i, j, tl);
      else if (i == 0 && j == s->width-1) mvwaddch(s->win, i, j, tr);
      else if (i == s->height-1 && j == 0) mvwaddch(s->win, i, j, bl);
      else if (i == s->height-1 && j == s->width-1) mvwaddch(s->win, i, j, br);

      else if (i == 0) mvwaddch(s->win, i, j, h);            // Top border
      else if (i == s->height-1) mvwaddch(s->win, i, j, h);  // Bottom border

      else if (j == 0) mvwaddch(s->win, i, j, v);            // Left border
      else if (j == s->width-1) mvwaddch(s->win, i, j, v);   // Right border
    }
  }

  ac_changeColor(s, s->color);
}


//////////////////// Menu /////////////////////
// A menu is syntactic sugar for a screen
ACmenu *ac_menuInit(int height, int width, int start_y, int start_x)
{
  ACmenu *m = ac_screenInit(height, width, start_y, start_x);
  return m;
}

void ac_menuSetTitle(ACmenu *m, char *name, int color, int pos, int offset)
{
  ac_setTitle(m, name, color, pos, offset);
}

// Set starting position of a menu's item list
void ac_itemStart(ACmenu *m, int y, int x, int height, int width)
{
  if (y < 0) y = 0;
  if (y > m->height) y = m->height-m->border_offset;
  if (x < 0) x = 0;
  if (x > m->width) y = m->width-m->border_offset;
  m->item_start_y = y;
  m->item_start_x = x;

  if (y + height > m->height) height = m->height-m->border_offset - y;
  if (x + width > m->width) width = m->width-m->border_offset - x;
  m->item_height = height;
  m->item_height = width;
  m->item_end_y = y + height;
  if (m->item_end_y > m->height) m->item_end_y = m->height-m->border_offset;
  m->item_end_x = x + width;
  if (m->item_end_x > m->width) m->item_end_x = m->width-m->border_offset;
  m->bot_visible -= m->item_start_y-1;
}

// Add a string to the end of a menu's item list
void ac_addItem(ACmenu *m, char *str)
{
  m->nitems++;
  if (m->nitems <= (m->height - m->border_offset)) m->bot_visible++;
  m->items = (char **) realloc(m->items, m->nitems * sizeof(*m->items));
  m->items[m->nitems-1] = (char *) calloc(1, sizeof(char)*strlen(str)+1);
  strncpy(m->items[m->nitems-1], str, strlen(str));
}

void ac_addItems(ACmenu *m, char **items, int nitems)
{
  int i;
  for (i = 0; i < nitems; i++){
    ac_addItem(m, items[i]);
  }
}

// Highlight a line based on screen's highlight settings
void ac_highlight(ACmenu *m, int y, int x)
{
  int i;


  if (!m->hl_line && !m->hl_forward && !m->hl_backward) return;

  ac_changeColor(m, m->hl_color);

  if (m->hl_line){
    for (i = 1; i < m->width-1; i++){
      mvwaddch(m->win, y, i, ' ');
    }
    ac_changeColor(m, m->color);
    return;
  }

  if (m->hl_forward > 0){
    for (i = 0; i < m->hl_forward; i++){
      mvwaddch(m->win, y, x+i, ' ');
    }
  }

  if (m->hl_backward > 0){
    for (i = 0; i < m->hl_backward; i++){
      mvwaddch(m->win, y, x-i-1, ' ');
    }
  }

  ac_changeColor(m, m->color);
}

// Truncate a string which is too long for a menu and append a runoff string
void ac_truncateString(ACmenu *m, char *str, const char *runoff)
{
  char tmp[m->width];
  memset(tmp, 0, m->width);
  int len = m->width - m->border_offset - strlen(runoff);
  strncpy(tmp, str, len);
  memset(str, 0, strlen(str));
  strncpy(str, tmp, len);
  strncat(str, runoff, strlen(runoff));
}

void scrollDown(ACmenu *m, int n)
{
  m->top_visible += n;
  m->bot_visible += n;
  werase(m->win);
}

void scrollUp(ACmenu *m, int n)
{
  m->top_visible -= n;
  m->bot_visible -= n;
  werase(m->win);
}

void ac_drawMenu(ACmenu *m)
{
  int i, j, k;
  const char *runoff = "...\0";

  int index = 0;
  for (i = m->top_visible; i < m->bot_visible; i++){
    if (m->bot_visible > m->nitems) {
      endwin();
      exit(1);
    }
    char *str = m->items[i];
    int scrolloff = m->scrolloff;
    int overflow = m->cur_item + scrolloff;

    // Adjust scrolloff to avoid end collisions
    if (overflow >= m->nitems)          scrolloff = 0;
    else if (m->cur_item-scrolloff < 0) scrolloff = 0;

    // Scroll down if current item extends beyond menu bounds
    if (m->cur_item + scrolloff > m->bot_visible){
      scrollDown(m, overflow - m->bot_visible + 1);
      ac_drawMenu(m);
      return;
    }

    // Scroll up if current item extends beyond menu bounds
    if (m->cur_item - scrolloff < m->top_visible){
      scrollUp(m, m->top_visible - m->cur_item + scrolloff);
      ac_drawMenu(m);
      return;
    }

    // Truncate names which are too long for the menu
    if (strlen(m->items[i]) > m->width - m->border_offset){
      ac_truncateString(m, m->items[i], runoff);
    }

    // Draw current menu item highlighted
    if (i == m->cur_item){
      ac_highlight(m, m->item_start_y+index, m->item_start_x);
      ac_changeColor(m, m->hl_color);
      mvwaddstr(m->win, m->item_start_y+index, m->item_start_x, str);
      ac_changeColor(m, m->color);
    }
    // Draw other menu items unhighlighted
    else{
      for (j = strlen(str)+m->border_offset/2; j < m->width-m->border_offset/2; j++){
        mvwaddch(m->win, m->item_start_y+index, j, ' ');
      }
      mvwaddstr(m->win, m->item_start_y+index, m->item_start_x, str);
    }
    index++;
  }
}

// Iterate down the item list
void ac_itemNext(ACmenu *m)
{
  if (!m->wrap && m->cur_item == m->nitems-1) return;
  m->cur_item = (m->cur_item + 1) % m->nitems;
}

// Iterate up the item list
void ac_itemPrev(ACscreen *m)
{
  if (!m->wrap && m->cur_item == 0) return;
  m->cur_item--;
  if (m->cur_item < 0) m->cur_item = m->nitems-1;
}

// Jump down the item list by n
void ac_itemNextn(ACmenu *m, int n)
{
  int i;
  for (i = 0; i < n; i++) ac_itemNext(m);
}

// Jump up the item list by n
void ac_itemPrevn(ACscreen *m, int n)
{
  int i;
  for (i = 0; i < n; i++) ac_itemPrev(m);
}

// Jump to the item n
void ac_itemSet(ACscreen *m, int n)
{
  if (n < 0 || n > m->nitems-1) return;
  m->cur_item = n;
}

////////////////////// Print /////////////////////////////
/*
  Prints a string at position x,y.
  Then, pads the characters after the string
  with spaces until field_size is reached.

  Returns the index where the padding ends.
  Ex. of two rows of four fields with field_size=20 (top row is for measuring):
  FIELD ONE-----------FIELD TWO-----------FIELD THREE---------FIELD FOUR----------
  ITEM NAME:          Computer XT         CATEGORIES:         AC
  MODEL:              Generic             SERIAL NUMBER:      9382 9943 4324 32223

  To use this function effectively, declare an int such as cursorPosX
  set to the x position of field one (0 in the above example) and
  pass it into print_field in place of x.
  Then, for every field after, invoke ac_printField() by passing 
  cursorPosX += field_size in place of x.

  Example:
  int cursorPosX = 0;
  ac_printField(screen, 0, cursorPosX, field_size, "FIELD ONE");
  ac_printField(screen, 0, cursorPosX += field_size, field_size, "FIELD TWO");
  ac_printField(screen, 0, cursorPosX += field_size, field_size, "FIELD THREE");
  ac_printField(screen, 0, cursorPosX += field_size, field_size, "FIELD FOUR");

  The ac_printFields() function below will do this for you via a 2d char array
  you pass it. However, it won't allow you for finer control such as changing
  the field's color between prints.
*/
int ac_printField(ACscreen *s, int y, int x, int field_size, char field[])
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

// Calls ac_printField() for every field passed thru the fields array.
// Simplifies field printing but does not allow for changing color between fields.
void ac_printFields(ACscreen *s, int y, int x, int field_size, char *fields[], int nfields)
{
  int i;
  int cursorPosX = 3;

  for (i = 0; i < nfields; i++){
    ac_printField(s, y, cursorPosX+(field_size*i), field_size, fields[i]);
  }
}

// Draw a horizontal line across row y using character c.
// Pass in 1 for overwrite_border to draw the line on top of the border edges.
// Pass in 0 to only draw from 1 to width-1, keeping the border intact.
void ac_drawLineH(ACscreen *s, int y, char c, int overwrite_border)
{
  int i;
  if (overwrite_border){
    for (i = 0; i < s->width; i++) mvwaddch(s->win, y, i, c);
  }
  else{
    for (i = 1; i < s->width-1; i++) mvwaddch(s->win, y, i, c);
  }
}

// Draw a vertical line down column x using character c.
// Pass in 1 for overwrite_border to draw the line on top of the border edges.
// Pass in 0 to only draw from 1 to height-1, keeping the border intact.
void ac_drawLineV(ACscreen *s, int x, char c, int overwrite_border)
{
  int i;
  if (overwrite_border){
    for (i = 0; i < s->height; i++) mvwaddch(s->win, i, x, c);
  }
  else{
    for (i = 1; i < s->height-1; i++) mvwaddch(s->win, i, x, c);
  }
}

// Print a string in the middle of the screen of row y
int ac_printCenter(ACscreen *s, int y, char *str)
{
  int middle = get_middle(s->width);
  int pos = middle - strlen(str) / 2;
  mvwaddstr(s->win, y, pos, str);
}

// Print a string on the right of the screen of row y;
// To give some offset or prevent colliding with the right border,
//   pass a number in for offset. offset=0 will print all the way to the
//   end of the screen while offset=1 will leave a free space on the right
//   for something like the border or padding.
int ac_printRight(ACscreen *s, int y, char *str, int offset)
{
  int right = s->width - offset;
  int pos = right - strlen(str);
  mvwaddstr(s->win, y, pos, str);
}

// Print a string at the desired position, cycling through colors
// to allow for easy multicolored text.
void ac_rainbow(ACscreen *s, int y, int x, char *str, int colors[], int ncolors)
{
  int i;
  for (i = 0; i < strlen(str); i++){
    ac_changeColor(s, colors[i % ncolors]);
    mvwaddch(s->win, y, x+i, str[i]);
  }
}

// Print a string with n spaces between each character
void ac_printSpace(ACscreen *s, int y, int x, char *str, int n)
{
  int i;
  int offset = 0;
  for (i = 0; i < strlen(str); i++){
    mvwaddch(s->win, y, x+i+offset, str[i]);
    offset += n;
  }
}

// Print a string vertically downwards
void ac_printV(ACscreen *s, int  y, int x, char *str)
{
  int i;
  for (i = 0; i < strlen(str); i++){
    mvwaddch(s->win, y+i, x, str[i]);
  }
}

// Print a string vertically downwards with n spaces between each character
void ac_printSpaceV(ACscreen *s, int y, int x, char *str, int n)
{
  int i;
  int offset = 0;
  for (i = 0; i < strlen(str); i++){
    mvwaddch(s->win, y+i+offset, x, str[i]);
    offset += n;
  }
}


///////////////////// Slider ////////////////////////////////
// Initialize a slider with parameters and default values
ACslider *ac_sliderInit(ACscreen *parent, int min, int max, int length, int width, int start_y, int start_x)
{
  // Set necessary values based on parameters
  ACslider *s = calloc(1, sizeof(ACslider));;
  s->parent = parent;
  s->min = min;
  s->max = max;
  s->length = length;
  s->width = width+2;
  s->start_y = start_y;
  s->start_x = start_x;

  // Set default values (must be changed manually)
  s->val = 0;
  s->border = 1;
  s->orientation = SLIDER_H;
  s->label[0] = '\0';
  s->color_fill = s->color_border = s->color_label = s->color_val = WH_BK;
  s->h = '-';
  s->v = '|';
  s->c = '+';
  s->empty = ' ';
  s->fill = '=';
  s->wrap = 0;
  s->print_val = 0;

  return s;
}

void ac_sliderSetLabel(ACslider *s, const char *str)
{
  memset(s->label, 0, CMAX);
  strncpy(s->label, str, strlen(str));
}

void ac_sliderSetPos(ACslider *s, int y, int x)
{
  s->start_y = s->parent->start_y + y;
  s->start_x = s->parent->start_x + x;
}

// Set every color option in the slider
void ac_sliderColorAll(ACslider *s, int color)
{
  s->color_fill = s->color_border = s->color_label = s->color_val = color;
}

// Draw a slider at its position in its parent window
void ac_sliderDraw(ACslider *s)
{
  int i, j;
  int start_y, start_x;  // Relative to stdscr
  int end_y, end_x;
  start_y = s->parent->start_y + s->start_y;
  start_x = s->parent->start_x + s->start_x;

  ac_changeColor(s->parent, s->color_border);

  // Draw border by creating subwindow in parent
  delwin(s->win);
  if (s->orientation == SLIDER_H){
    end_y = s->width;
    end_x = s->length;
  }
  else{
    end_y = s->length;
    end_x = s->width;
  }
  s->win = subwin(s->parent->win, end_y, end_x, start_y, start_x);
  wborder(s->win, 0, 0, 0, 0, 0, 0, 0, 0);

  // Label relative to parent window
  if (s->label[0] != '\0'){
    ac_changeColor(s->parent, s->color_label);
    mvwaddstr(s->parent->win, s->start_y+end_y, s->start_x, s->label);
    mvwaddstr(s->parent->win, s->start_y+end_y, s->start_x, s->label);
  }

  // Value relative to label
  if (s->print_val){
    ac_changeColor(s->parent, s->color_val);
    mvwaddstr(s->parent->win, s->start_y+end_y, s->start_x+strlen(s->label), "                ");
    mvwprintw(s->parent->win, s->start_y+end_y, s->start_x+strlen(s->label), "%d", s->val);
  }

  int ypos = s->start_y-2;
  int xpos = s->start_x;
  int size = (s->val - s->min) * (s->length-2) / (s->max - s->min);

  // redraw empty first
  for (i = 0; i < s->length-2; i++){
    for (j = 0; j < s->width-2; j++){
      if (s->orientation == SLIDER_H) mvwaddch(s->parent->win, ypos+j+3, xpos+i+1, s->empty);
      else                            mvwaddch(s->parent->win, ypos+s->length-i, xpos+j+1, s->empty);
    }
  }

  // draw fill
  for (i = 0; i < size; i++){
    for (j = 0; j < s->width-2; j++){
      if (s->orientation == SLIDER_H) mvwaddch(s->parent->win, ypos+j+3, xpos+i+1, s->fill);
      else                            mvwaddch(s->parent->win, ypos+s->length-i, xpos+j+1, s->fill);
    }
  }

  ac_changeColor(s->parent, s->parent->color);
}

////////////////// Menu /////////////////////////
void ac_menuDraw(ACmenu *m)
{
  int i;
//  ac_changeColor(m->parent, m->border_color);
  wborder(m->win, 0, 0, 0, 0, 0, 0, 0, 0);
//  ac_changeColor(m->parent, m->color);
}


////////////// Initialize, Destroy, Refresh ///////////////////
// There is no need to call this since it's called by ac_colorStart()
// Initialize the color pairs found in the COLORS enum.
// Two color pairs per line to save vertical space.
void ac_colorPairsInit()
{
  init_pair(WH_WH, COLOR_WHITE, COLOR_WHITE);   init_pair(BL_WH, COLOR_BLUE, COLOR_WHITE);
  init_pair(BK_WH, COLOR_BLACK, COLOR_WHITE);   init_pair(GR_WH, COLOR_GREEN, COLOR_WHITE);
  init_pair(CY_WH, COLOR_CYAN, COLOR_WHITE);    init_pair(YL_WH, COLOR_YELLOW, COLOR_WHITE);
  init_pair(RD_WH, COLOR_RED, COLOR_WHITE);     init_pair(MG_WH, COLOR_MAGENTA, COLOR_WHITE);
  init_pair(WH_BL, COLOR_WHITE, COLOR_BLUE);    init_pair(BL_BL, COLOR_BLUE, COLOR_BLUE);
  init_pair(BK_BL, COLOR_BLACK, COLOR_BLUE);    init_pair(GR_BL, COLOR_GREEN, COLOR_BLUE);
  init_pair(CY_BL, COLOR_CYAN, COLOR_BLUE);     init_pair(YL_BL, COLOR_YELLOW, COLOR_BLUE);
  init_pair(RD_BL, COLOR_RED, COLOR_BLUE);      init_pair(MG_BL, COLOR_MAGENTA, COLOR_BLUE);
  init_pair(WH_BK, COLOR_WHITE, COLOR_BLACK);   init_pair(BL_BK, COLOR_BLUE, COLOR_BLACK);
  init_pair(BK_BK, COLOR_BLACK, COLOR_BLACK);   init_pair(GR_BK, COLOR_GREEN, COLOR_BLACK);
  init_pair(CY_BK, COLOR_CYAN, COLOR_BLACK);    init_pair(YL_BK, COLOR_YELLOW, COLOR_BLACK);
  init_pair(RD_BK, COLOR_RED, COLOR_BLACK);     init_pair(MG_BK, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(WH_GR, COLOR_WHITE, COLOR_GREEN);   init_pair(BL_GR, COLOR_BLUE, COLOR_GREEN);
  init_pair(BK_GR, COLOR_BLACK, COLOR_GREEN);   init_pair(GR_GR, COLOR_GREEN, COLOR_GREEN);
  init_pair(CY_GR, COLOR_CYAN, COLOR_GREEN);    init_pair(YL_GR, COLOR_YELLOW, COLOR_GREEN);
  init_pair(RD_GR, COLOR_RED, COLOR_GREEN);     init_pair(MG_GR, COLOR_MAGENTA, COLOR_GREEN);
  init_pair(WH_CY, COLOR_WHITE, COLOR_CYAN);    init_pair(BL_CY, COLOR_BLUE, COLOR_CYAN);
  init_pair(BK_CY, COLOR_BLACK, COLOR_CYAN);    init_pair(GR_CY, COLOR_GREEN, COLOR_CYAN);
  init_pair(CY_CY, COLOR_CYAN, COLOR_CYAN);     init_pair(YL_CY, COLOR_YELLOW, COLOR_CYAN);
  init_pair(RD_CY, COLOR_RED, COLOR_CYAN);      init_pair(MG_CY, COLOR_MAGENTA, COLOR_CYAN);
  init_pair(WH_YL, COLOR_WHITE, COLOR_YELLOW);  init_pair(BL_YL, COLOR_BLUE, COLOR_YELLOW);
  init_pair(BK_YL, COLOR_BLACK, COLOR_YELLOW);  init_pair(GR_YL, COLOR_GREEN, COLOR_YELLOW);
  init_pair(CY_YL, COLOR_CYAN, COLOR_YELLOW);   init_pair(YL_YL, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(RD_YL, COLOR_RED, COLOR_YELLOW);    init_pair(MG_YL, COLOR_MAGENTA, COLOR_YELLOW);
  init_pair(WH_RD, COLOR_WHITE, COLOR_RED);     init_pair(BL_RD, COLOR_BLUE, COLOR_RED);
  init_pair(BK_RD, COLOR_BLACK, COLOR_RED);     init_pair(GR_RD, COLOR_GREEN, COLOR_RED);
  init_pair(CY_RD, COLOR_CYAN, COLOR_RED);      init_pair(YL_RD, COLOR_YELLOW, COLOR_RED);
  init_pair(RD_RD, COLOR_RED, COLOR_RED);       init_pair(MG_RD, COLOR_MAGENTA, COLOR_RED);
  init_pair(WH_MG, COLOR_WHITE, COLOR_MAGENTA); init_pair(BL_MG, COLOR_BLUE, COLOR_MAGENTA);
  init_pair(BK_MG, COLOR_BLACK, COLOR_MAGENTA); init_pair(GR_MG, COLOR_GREEN, COLOR_MAGENTA);
  init_pair(CY_MG, COLOR_CYAN, COLOR_MAGENTA);  init_pair(YL_MG, COLOR_YELLOW, COLOR_MAGENTA);
  init_pair(RD_MG, COLOR_RED, COLOR_MAGENTA);   init_pair(MG_MG, COLOR_MAGENTA, COLOR_MAGENTA);
}

// Start the ncurses colors
// Set up default RGB values for the 8 colors
// Call ac_colorPairsInit()
void ac_colorStart()
{
  start_color();
  init_color(COLOR_WHITE,   255, 255, 255);
  init_color(COLOR_BLUE,     52,  91, 133);
  init_color(COLOR_BLACK,    31,  37,  32);
  init_color(COLOR_GREEN,    64, 255,  83);
  init_color(COLOR_CYAN,     29, 199, 252);
  init_color(COLOR_YELLOW,  255, 255,  85);
  init_color(COLOR_MAGENTA, 255,   0, 255);
  ac_colorPairsInit();
}

// Redraw all screen properties (if they are set).
void ac_refresh(ACscreen *s)
{
  ac_drawMenu(s);
  ac_drawBorder(s);
  ac_drawTitle(s);
  wrefresh(s->win);
}

char ac_getch(ACscreen *s)
{
  char ch = wgetch(s->win);
  ac_refresh(s);
  return ch;
}

void ac_init()
{
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  nodelay(stdscr, 1);
  curs_set(0);
  ac_colorStart();
  clear();
}

// It's just endwin()
void ac_end()
{
  endwin();
}
