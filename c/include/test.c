#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addItems(char *items, int nitems)
{
  int i;
  char *p = items;
  for (i = 0; i < nitems; i++){
    printf("%c", *p);
    while(*p) p++;
  }
}

int main()
{
  char items[3][80];
  strcpy(items[0], "Billy");
  strcpy(items[1], "Mandy");
  strcpy(items[2], "Grim");
  addItems(items[0], 3);
}
