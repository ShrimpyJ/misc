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

   Also defines a visual slider which contains a value within a set range
   and gives functionality for printing it horizontally or vertically.
*/

// Default characters for drawing a border
#define LINE_H    '-'  // Horizontal border
#define LINE_V    '|'  // Vertical border
#define LINE_TL   '┌'  // Corner top left
#define LINE_TR   '┐'  // Corner top right
#define LINE_BL   '└'  // Corner bot left
#define LINE_BR   '┘'  // Corner bot right

#define CMAX     80    // Max char array length

#define LEFT    0
#define CENTER  1
#define MIDDLE  1
#define RIGHT   2

#define SLIDER_V   0
#define SLIDER_H   1


// Updates every time a new screen is created below the bottommost.
// If passed into ac_screenInit() in place of start_y,
// allows new window to be placed directly below bottommost screen.
extern int AC_YPOS;

// Color pairs.
// Left side of underscore is foreground
// Right side of underscore is background
extern enum AC_COLOR { WH_WH, BL_WH, BK_WH, GR_WH, CY_WH, YL_WH, RD_WH, MG_WH,
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

  int color;
  int field_size;

  // Screen title settings (set with ac_setTitle())
  // Title is NULL by default and can only be drawn
  // if set. When set, draw it with ac_drawTitle().
  char title[CMAX];  // Defaults to NULL
  int title_color;   // Defaults to WH_BK
  int title_pos;     // LEFT=0  MIDDLE=1  RIGHT=0 defaults to MIDDLE
  int title_offset;  // Only for LEFT or RIGHT defaults to 0

  // Screen border settings (change with ac_setBorder())
  // By default, a border is created when ac_screenInit()
  // is called. The border must still be drawn with 
  // ac_drawBorder()  or ac_drawBorderCh() to be seen however.
  // A border can be removed with ac_unsetBorder().
  // An unset border will not be drawn even when 
  // ac_drawBorder() or ac_drawBorderCh() is called.
  int has_border;    // Defaults to 1
  int border_color;  // Defaults to WH_BK
  int border_offset; // Defaults to 2 (for each side horizontally or vertically)
  int h;
  int v;
  int tl, tr, bl, br;

  // Highlight settings
  int hl_color;     // Defaults to BK_WH
  int hl_line;      // Bool: 1 will highlight the entire horizontal
                    //       line minus the border
                    //       Default is 0, which only highlights the
                    //       selected text
  int hl_forward;   // Constant. Set to always highlight n spaces forwards
                    // starting at the first character of the item.
  int hl_backward;  // Constant. Set to always highlight n spaces backwards
                    // starting at the first character of the item.

  // Menu settings
  int nitems;          // Defaults to 0
  char **items;
  int cur_item;        // Currently selected item (defaults to 0)
  int item_start_y;
  int item_start_x;
  int item_end_y;
  int item_end_x;
  int item_height;
  int item_width;
  int items_visible;   // Total # of visible items
  int top_visible;     // Track the top and bottom visible
  int bot_visible;     // items to enable scrolling.
  int wrap;            // Bool: 1 allows wrapping when reaching end of menu
                       // Default: 0
  int scrolloff;       // Set to view more lines ahead when scrolling
                       // Default: 1
} ACscreen;

/*
  A slider to visually represent a certain value within a given range.
  Sliders must have a parent screen which will determine their placement.
  i.e. a slider at the default value 0,0 will be in the top left corner
  of its parent screen's window.

  A lot of values are not passed into or set in the init function,
  these must be set manually.
*/
typedef struct ac_slider {
  // The following must be passed into ac_sliderInit()
  ACscreen *parent; // Which screen the slider will be drawn on
  int min;          // Min value the slider can represent
  int max;          // Max value the slider can represent
  int length;       // How long the slider will be. Add 1 to each end for
                    // drawing the border (so length=3 would be drawn as 5)
  int width;        // How wide the slider will be. 

  WINDOW *win;      // Subwindow of parent screen's window

  // The following must be set manually according to your needs
  int val;          // Current value the slider represents
                    // Default: 0
  int start_y;      // Default: 0
  int start_x;      // Default: 0
  int border;       // Bool: 0 will not draw a border around the slider
                    // Default: 1
  int orientation;  // Default: SLIDER_H (0)
  char label[CMAX]; // Drawn underneath the slider if exists
  int color_fill;   // Default: WH_BK
  int color_border; // Default: WH_BK
  int color_label;  // Default: WH_BK
  int color_val;    // Default: WH_BK
  char h, v, c;     // Horizontal, vertical, corner chars
                    // Default: h='-' v='|' c='+'
  char empty, fill; // For drawing the progress bar
                    // Default: empty=' ' fill='='
  int wrap;         // Bool: 0 prevents slider from wrapping around to
                    //       the opposite side on overflow/underflow
                    // Default: 0
  int print_val;    // Bool: 1 will print the current value at the end
                    //       of the label (or where the label would be)
                    // Default: 0
} ACslider;

/*
  An interactive menu 
*/
//typedef struct ac_menu {
//  ACscreen *parent;
//  int nitems;
//  char *items[CMAX];
//
//  int color;          // Default: WH_BK
//  int border_color;   // Default: WH_BK
//  WINDOW *win;
//
//  // Title settings
//  char title[CMAX];   // Default: NULL
//  int title_color;    // Default: WH_BK
//  int title_pos;      // Default: CENTER
//  int title_offset;   // Default: 0
//} ACmenu;

typedef ACscreen ACmenu;

// Screen functions
ACscreen *ac_screenInit(int height, int width, int start_y, int start_x);
void ac_changeColor(ACscreen *s, int pair);
void ac_setTitle(ACscreen *s, char *name, int color, int pos, int offset);
void ac_unsetTitle(ACscreen *s);
void ac_unsetBorder(ACscreen *s);
void ac_drawTitle(ACscreen *s);
void ac_drawBorder(ACscreen *s);
void ac_drawBorderCh(ACscreen *s);

// Menu functions (menus are syntactic sugar for screens)
ACmenu *ac_menuInit(int height, int width, int start_y, int start_x);
void ac_menuSetTitle(ACmenu *m, char *name, int color, int pos, int offset);
void ac_itemStart(ACmenu *m, int y, int x, int height, int width);
void ac_addItem(ACmenu *m, char *str);
void ac_addItems(ACmenu *m, char **items, int nitems);
void ac_highlight(ACmenu *m, int y, int x);
void ac_truncateString(ACmenu *m, char *str, const char *runoff);
void ac_drawMenu(ACmenu *m);
void ac_itemNext(ACmenu *m);
void ac_itemPrev(ACmenu *m);
void ac_itemNextn(ACmenu *m, int n);
void ac_itemPrevn(ACscreen *m, int n);
void ac_itemSet(ACscreen *m, int n);

// Print functions
int ac_printField(ACscreen *s, int y, int x, int field_size, char field[]);
void ac_printFields(ACscreen *s, int y, int x, int field_size, char *fields[], int nfields);
void ac_drawLineH(ACscreen *s, int y, char c, int overwrite_border);
void ac_drawLineV(ACscreen *s, int x, char c, int overwrite_border);
int ac_printCenter(ACscreen *s, int y, char *str);
int ac_printRight(ACscreen *s, int y, char *str, int offset);
void ac_rainbow(ACscreen *s, int y, int x, char *str, int colors[], int ncolors);
void ac_printSpace(ACscreen *s, int y, int x, char *str, int n);
void ac_printV(ACscreen *s, int  y, int x, char *str);
void ac_printSpaceV(ACscreen *s, int y, int x, char *str, int n);

// Slider functions
ACslider *ac_sliderInit(ACscreen *parent, int min, int max, int length, int width, int start_y, int start_x);
void ac_sliderSetLabel(ACslider *s, const char *str);
void ac_sliderSetPos(ACslider *s, int y, int x);
void ac_sliderDraw(ACslider *s);
void ac_sliderSetLabel(ACslider *s, const char *str);
void ac_sliderColorAll(ACslider *s, int color);

// Menu functions
void ac_menuDraw(ACmenu *m);

// Initialize, destroy, refresh
void ac_colorPairsInit();
void ac_colorStart();
void ac_refresh(ACscreen *s);
char ac_getch(ACscreen *s);
void ac_init();
void ac_end();

#endif
