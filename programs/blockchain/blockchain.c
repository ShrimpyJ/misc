#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "blockchain.h"

blockchain *blockchain_init()
{
  blockchain *bc = calloc(1, sizeof(blockchain));
  block_t *block = calloc(1, sizeof(block_t));
  block->prev = NULL;
  block->next = NULL;
  block->id = rand() % MAX;
  bc->first = block;
  bc->last = block;
  return bc;
}

block_t *blockchain_create()
{
  block_t *block = calloc(1, sizeof(block_t));
  block->prev = NULL;
  block->next = NULL;
  return block;
}

int blockchain_verify(blockchain *bc, block_t *cur)
{
  block_t *last = bc->last;

  if (cur->id - last->id == 1) return 0;
  return -1;
}

int blockchain_append(blockchain *bc, block_t *block)
{
  if (blockchain_verify(bc, block) < 0) return -1;

  bc->last->next = block;
  bc->last = block;
  return 0;
}

void blockchain_print(blockchain *bc)
{
  block_t *cur = bc->first;
  while (cur){
    printf("ID: %d\n", cur->id);
    cur = cur->next;
  }
}

int main()
{
  int i;
  int n = 100;
  int r;
  char c;

  srand(time(NULL));

  blockchain *bc = blockchain_init();
  while(1){
    block_t *block = blockchain_create();
    block->id = rand() % MAX;
    if (blockchain_append(bc, block) < 0){
      continue;
    }
    printf("Inserting block...\n");
    blockchain_print(bc);
  }
}
