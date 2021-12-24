#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#define MAX 96532163

typedef struct block
{
  struct block *prev;
  struct block *next;
  uint64_t id;
} block_t;

typedef struct Blockchain
{
  block_t *first;
  block_t *last;
} blockchain;

extern blockchain *blockchain_init();
extern int blockchain_add(blockchain *bc, block_t *block);

#endif
