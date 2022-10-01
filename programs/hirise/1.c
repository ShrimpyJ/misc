#include <stdio.h>
#include <stdlib.h>

void set_int(void *p, int val)
{
  int *ip;
  ip = &val;
  p = (int *) ip;
}

int main(int argc, char **argv)
{
  void *p;
  set_int(p, 3);
  printf("%d\n", (int *) *p);
}
