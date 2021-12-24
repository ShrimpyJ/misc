#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING 0
#define INT    1
#define FLOAT  2

struct employee
{
  char name[50];
  char designation[50];
  int age;
  float salary;
  int index;
};

int mysscanf(const char *src, char *dst)
{
  char *p = src;
  //int i = strlen(src);
  while (*p != ':'){
    if (*p == '\0') return 0;
    *dst = *p;
    p++;
    dst++;
  }
  *dst = '\0';
  return 1;
}

void add_item(struct employee *e, const char *item)
{
  switch (e->index){
    case 0:
      sscanf(item, "%s", e->name);
    break;

    case 1:
      sscanf(item, "%s", e->designation);
    break;

    case 2:
      sscanf(item, "%d", &e->age);
    break;

    case 3:
      sscanf(item, "%f", &e->salary);
    break;
  }
  e->index++;
}

void add_employee(struct employee *e, struct employee **elist)
{
}

int main()
{
  int i;
  char item[40];
  int index = 0;
  FILE *fp = fopen("junk.txt", "r");
  struct employee *e;
  struct employee **elist;
  int size = 0;
  int inc = 1024;
  char buf[inc+4];

  e = malloc(sizeof(struct employee));
  memset(e, 0, sizeof(struct employee));
  e->index = 0;
  while (fread(buf, inc, 1, fp) > 0){
    size += inc;
  }
  printf("size: %d\n", size);
  char *raw;
  raw = calloc(size*2, sizeof(char));
  index = 0;
  int ret = 1;
  fclose(fp);
  fopen("junk.txt", "r");
  while ((ret = fread(buf, 1, inc, fp)) > 0){
    strcpy(raw+index, buf);
    index += ret;
  }

  char *p;
  p = &raw[0];
  char cur[50];
  while (mysscanf(p, cur) == 1){
    //printf("%s\n", cur);
    while (*p != ':' && *p != ','){
      p++;
    }
    memset(cur, 0, 50);
    p++;
  }
  fclose(fp);
}
