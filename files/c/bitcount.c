#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

void print_bits64(uint64_t n)
{
  while(n){
    if (n & 1) printf("1");
    else printf("0");
    n >>= 1;
  }
  printf("\n");
}

int bitcountEZ(uint64_t n)
{
  int count = 0;
  while(n){
    if (n & 1) count++;
    n >>= 1;
  }
  return count;
}

int bitcount(uint64_t arr[])
{
  int count = 0;
  uint64_t *index = &arr[0];

  while (*index){
    uint64_t n = *index;
    while (n){
      n = n & (n - 1);
      count++;
    }
    index += 1;
  }

  return count;
}

int main(int argc, char **argv)
{
  int i;
  int size = 1000000;
  uint64_t max = 9999999999999;
  uint64_t arr[size];
  memset(arr, 0, size*sizeof(uint64_t));
  int count = 0;

  srand(time(NULL));
  if (argc != 2) exit(0);
  
  for (i = 0; i < size; i++){
    arr[i] = rand() % max;
  }

  if (strcmp("1", argv[1]) == 0 || strcmp("3", argv[1]) == 0){
    printf("one at a time\n");
    for (i = 0; i < size; i++){
      count += bitcountEZ(arr[i]);
    }
    printf("total: %d\n", count);
  }

  if (strcmp("2", argv[1]) == 0 || strcmp("3", argv[1]) == 0){
    printf("shifting\n");
    printf("total: %d\n", bitcount(arr));
  }
}
