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
#define LINE_V    '|'  // Vertical border
#define LINE_H    '-'  // Horizontal border
#define LINE_C    '+'  // Corner

#define CMAX     80    // Max char array length

// Updates every time a new window is created.
// If passed into ac_screenInit() in place of start_y,
// allows new window to be placed directly below
// the most recent window. Always updates on ac_screenInit().
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
  int color_pair;
  int field_size;
} ACscreen;

/*
  A slider to visually represent a certain value within a given range.
  Sliders must have a parent screen which will determine their placement.
  i.e. a slider at the default value 0,0 will be in the top left corner
  of its parent screen's window.

  A lot of values are not passed into or set in the init function,
  these must be set manually.

  Example of a half full slider with default settings and length=8 and width=1:
  +--------+
  |====    |
  +--------+

  Example of a half full slider with default settings and length=8 and width=3:
  +--------+
  |====    |
  |====    |
  |====    |
  +--------+
*/
typedef struct slider {
  // The following must be passed into ac_sliderInit()
  ACscreen *parent; // Which screen the slider will be drawn on
  int min;          // Min value the slider can represent
  int max;          // Max value the slider can represent
  int length;       // How long the slider will be. Add 1 to each end for
                    // drawing the border (so length=3 would be drawn as 5)
  int width;        // How wide the slider will be. 

  // The following must be set manually according to your needs
  int val;          // Current value the slider represents
                    // Default: 0
  int start_y;      // Default: 0
  int start_x;      // Default: 0
  int border;       // Bool: 0 will not draw a border around the slider
                    // Default: 1
  int isHorizontal; // Default: 1
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
} Slider;

// Screen functions
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

// Initialize and destroy functions
void ac_init(int echo, int newline_mode);
void ac_end();
void ac_colorPairsInit();
void ac_colorStart();

// Slider functions
Slider *ac_sliderInit(ACscreen *parent, int min, int max, int length, int width);
void ac_sliderSetLabel(Slider *s, const char *str);
void ac_sliderDraw(Slider *s);
void ac_sliderSetLabel(Slider *s, const char *str);
void ac_sliderColorAll(Slider *s, int color);

#endif
