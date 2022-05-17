#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 99900
#define NASSETS 5000

typedef struct asset {
  int iarr[SIZE];
  double darr[SIZE];
  char carr[SIZE];
} Asset;

struct asset *asset_init()
{
  Asset *a = malloc(sizeof(Asset));
  for (int i = 0; i < SIZE; i++){
    a->iarr[i] = i;
    a->darr[i] = i * .05 * .005 * .0005;
    a->carr[i] = 'c';
  }
  return a;
}

char *convert_bytes(unsigned long bytes)
{
  char *ret = calloc(80, sizeof(char));
  char *rev = calloc(80, sizeof(char));
  char bytestr[80];
  int revindex = 0;

  sprintf(bytestr, "%ld", bytes);

  for (int i = strlen(bytestr); i > 0; i--){
    int index = abs(i - strlen(bytestr));
    if (index % 3 == 0 && index != 0){
      memcpy(rev+revindex, ",", 1);
      revindex++;
    }
    memcpy(rev+revindex, bytestr+i-1, 1);
    revindex++;
  }

  for (int i = strlen(rev); i > 0; i--){
    int index = abs(i - strlen(rev));
    memcpy(ret+index, rev+i-1, 1);
  }
  return ret;
}

int main(int argc, char** argv)
{
  Asset *pool[NASSETS];
  unsigned long bytes = 0;

  printf("Starting...\n");
  for (int i = 0; i < NASSETS; i++){
    Asset *a = asset_init();
    pool[i] = a;
    bytes += sizeof(Asset);
  }
  printf("Finished allocating %s bytes\n", convert_bytes(bytes));
  printf("  from %d assets (%s bytes each)\n\n", NASSETS, convert_bytes(sizeof(Asset)));

  for (int i = 0; i < NASSETS; i++){
    free(pool[i]);
  }
  printf("Finished freeing\n");
}
