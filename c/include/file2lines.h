#ifndef FILE2LINES_H
#define FILE2LINES_H

// Read a file into a 2d char array.
// Delimited by newline.

typedef struct {
  char **lines;
  int num_lines;
} file2lines;

extern file2lines *file2lines_read(char *file);
extern void file2lines_free(file2lines *f2l);

#endif
