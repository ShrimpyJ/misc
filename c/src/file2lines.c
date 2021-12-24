#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "file2lines.h"

file2lines *file2lines_read(char *file)
{
  char buffer[2];
  char *str;
  char *token;
  char **lines;
  int num_lines;
  int size;
  int i;
  int len;
  FILE *f;
  file2lines *f2l;

  f2l = calloc(1, sizeof(file2lines));

  if ((f = fopen(file, "r")) == NULL){
    perror(file);
    exit(1);
  }

  /* Get size of file first */
  size = 0;
  while ((fread(&buffer, 1, 1, f)) != 0) size++;

  /* Create string of entire file to be delimited later */
  str = malloc(sizeof(char) * size + 4);
  i = num_lines = 0;
  fseek(f, 0, SEEK_SET);
  while ((fread(&buffer, 1, 1, f)) != 0){
    str[i] = buffer[0];
    if (str[i] == '\n') num_lines++;
    i++;
  }

  /* Delimit file by newline */
  lines = (char **) calloc(num_lines+1, sizeof(char*));
  i = 0;
  token = strtok(str, "\n");
  len = strlen(token);
  while (token != NULL){
    len = strlen(token);
    lines[i] = (char *) calloc(len, sizeof(char));
    memcpy(lines[i], token, len);
    token = strtok(NULL, "\n");
    i++;
  }
  free(str);
  free(token);

  fclose(f);

  f2l->lines = lines;
  f2l->num_lines = num_lines;

  return f2l;
}

void file2lines_free(file2lines *f2l)
{
  int i;
  for (i = 0; i < f2l->num_lines; i++) free(f2l->lines[i]);
  free(f2l->lines);
  free(f2l);
}
