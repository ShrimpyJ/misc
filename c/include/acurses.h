#ifndef ACURSES_H
#define ACURSES_H

/*
   acurses.h

   A simple API layer for performing tasks in ncurses such as
   creating windows in descending order, drawing a border around
   a window, initializing every color pair, formatting fields
   to be left aligned, changing color pairs, drawing a line
   across a row or down a column, and printing a string in the
   middle or right side of the screen.

   For simplicity, the header file contains all the implementations.
   No .c files needed. Read up on the functions to get an idea of how
   to use them.
*/

// Default characters for drawing a border
#define LINE_V       '|'  // Vertical border
#define LINE_H       '-'  // Horizontal border
#define LINE_C       '+'  // Corner

// Updates every time a new window is created.
// If passed into ac_screenInit() in place of start_y,
// allows new window to be placed directly below
// the most recent window. Always updates on ac_screenInit().
int AC_YPOS = 0;

// Color pairs.
// Left side of underscore is foreground
// Right side of underscore is background
const enum AC_COLOR { WH_WH, BL_WH, BK_WH, GR_WH, CY_WH, YL_WH, RD_WH, MG_WH,
                      WH_BL, BL_BL, BK_BL, GR_BL, CY_BL, YL_BL, RD_BL, MG_BL,
                      WH_BK, BL_BK, BK_BK, GR_BK, CY_BK, YL_BK, RD_BK, MG_BK,
                      WH_GR, BL_GR, BK_GR, GR_GR, CY_GR, YL_GR, RD_GR, MG_GR,
                      WH_CY, BL_CY, BK_CY, GR_CY, CY_CY, YL_CY, RD_CY, MG_CY,
                      WH_YL, BL_YL, BK_YL, GR_YL, CY_YL, YL_YL, RD_YL, MG_YL,
                      WH_RD, BL_RD, BK_RD, GR_RD, CY_RD, YL_RD, RD_RD, MG_RD,
                      WH_MG, BL_MG, BK_MG, GR_MG, CY_MG, YL_MG, RD_MG, MG_MG
} ac_color;

// Contains a window with relevant data.
// field_size is only used to evenly space and 
// left-align strings based on its value.
// It is not set on ac_screenInit() and must be set manually.
typedef struct ac_screen {
  WINDOW *win;
  int height, width;
  int start_y, start_x;        // Absolute coordinates
  int mid_y, mid_x;
  int end_y, end_x;

  int start_yRel, start_xRel;  // Relative coordinates
  int mid_yRel, mid_xRel;
  int end_yRel, end_xRel;
  int color_pair;
  int field_size;
} ACscreen;

// All function delcarations for ease of reference
ACscreen *ac_screenInit(int height, int width, int start_y, int start_x);
void ac_drawBorder(ACscreen *s);
void ac_drawBorderCh(ACscreen *s, char horizontal, char vertical, char corner);
int ac_printField(ACscreen *s, int y, int x, int field_size, char field[]);
void ac_printFields(ACscreen *s, int y, int x, int field_size, char *fields[], int nfields);
void ac_changeColor(ACscreen *s, int pair);
void ac_drawLineH(ACscreen *s, int y, char c, int overwrite_border);
void ac_drawLineV(ACscreen *s, int x, char c, int overwrite_border);
int ac_printCenter(ACscreen *s, int y, char *str);
int ac_printRight(ACscreen *s, int y, char *str, int offset);
void ac_colorPairsInit();
void ac_colorStart();
void ac_init(int echo, int newline_mode);
void ac_close();
void ac_end();


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

  s->start_y = start_y;
  s->start_x = start_x;
  s->end_y = s->start_y + s->height;
  s->end_x = s->start_x + s->width;
  s->mid_y = s->end_y / 2;
  s->mid_x = s->end_x / 2;

  s->start_yRel = 0;
  s->start_xRel = 0;
  s->end_yRel = s->height-1;
  s->end_xRel = s->width-1;
  s->mid_yRel = s->end_yRel / 2;
  s->mid_xRel = s->end_xRel / 2;

  WINDOW *win = newwin(height, width, start_y, start_x);
  s->win = win;
  AC_YPOS += s->height;
  s->color_pair = WH_BK;
  return s;
}

/*
  Draws a border on the outer edges of the screen's window.
  Border characters are the defaults defined in the file opening.
  For alternate border drawing, use ac_drawBorderCh() below.

  Example of a default border for an 8x5 window:
  +------+
  |      |
  |      |
  |      |
  +------+

  Drawing a border is nice but also requires some attention when drawing
  text to avoid colliding with it. Pay attention to offsets.
*/
void ac_drawBorder(ACscreen *s)
{
  int i, j;
  va_list valist;
  char ch = LINE_H;
  char cv = LINE_V;
  char cc = LINE_C;

  for (i = 0; i < s->height; i++){
    for (j = 0; j < s->width; j++){
      // Draw corners
      if (i == 0           && j == 0 || i == 0           && j == s->width-1 ||
          i == s->height-1 && j == 0 || i == s->height-1 && j == s->width-1)
        mvwaddch(s->win, i, j, cc);

      else if (i == 0) mvwaddch(s->win, i, j, ch);            // Top border
      else if (i == s->height-1) mvwaddch(s->win, i, j, ch);  // Bottom border

      else if (j == 0) mvwaddch(s->win, i, j, cv);            // Left border
      else if (j == s->width-1) mvwaddch(s->win, i, j, cv);   // Right border
    }
  }
}

/*
  Identical to ac_drawBorder() but allows you to pass alternate characters
  to draw the border (horizontal, vertical, corner).

  Ex. passing ('0', '+', 'x') will draw the following border for an 8x5 window:
  x000000x
  +      +
  +      +
  +      +
  x000000x

  Drawing a border is nice but also requires some attention when drawing
  text to avoid colliding with it. Pay attention to offsets.
*/
void ac_drawBorderCh(ACscreen *s, char horizontal, char vertical, char corner)
{
  int i, j;
  char ch = horizontal;
  char cv = vertical;
  char cc = corner;

  for (i = 0; i < s->height; i++){
    for (j = 0; j < s->width; j++){
      // Draw corners
      if (i == 0           && j == 0 || i == 0           && j == s->width-1 ||
          i == s->height-1 && j == 0 || i == s->height-1 && j == s->width-1)
        mvwaddch(s->win, i, j, cc);

      else if (i == 0) mvwaddch(s->win, i, j, ch);            // Top border
      else if (i == s->height-1) mvwaddch(s->win, i, j, ch);  // Bottom border

      else if (j == 0) mvwaddch(s->win, i, j, cv);            // Left border
      else if (j == s->width-1) mvwaddch(s->win, i, j, cv);   // Right border
    }
  }
}

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

// Changes the color pair stored in a screen and updates the window
// Pass in an enum pair such as BL_BK for blue text on black background
void ac_changeColor(ACscreen *s, int pair)
{
  wattroff(s->win, COLOR_PAIR(s->color_pair));
  wattron(s->win, COLOR_PAIR(pair));
  s->color_pair = pair;
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
  int middle = s->width / 2;
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

// Doesn't need to be used, only initializes
// ncurses with basic values. Pass in 0 for echo
// to not have input echo back to the screen.
// Pass 0 in for newline_mode to not have key presses
// immediately be processed (i.e. wait until newline).
void ac_init(int echo, int newline_mode)
{
  initscr();
  if (!newline_mode) cbreak();
  keypad(stdscr, TRUE);
  if (!echo) noecho();
  curs_set(0);
  clear();
}

// It's just endwin()
void ac_close()
{
  endwin();
}

// In case people type the wrong thing (like I did)
void ac_end()
{
  endwin();
}

#endif
