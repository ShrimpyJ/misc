#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  int last, cur;
  int count = 0;
  int threshold = 30;

  srand(time(NULL));

  last = rand() % 2;
  count++;
  while(1){
    cur = rand() % 2;
    if (count >= threshold) printf("count: %d\n", count);
    if (cur == last) count++;
    else count = 0;
    last = cur;
  }
}
