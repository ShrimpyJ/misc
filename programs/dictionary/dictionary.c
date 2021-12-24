#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>
#include "file2lines.h"

#define FILE_NAME "/home/pete/words.txt"

typedef struct entry {
  int key;
  char *val;
  struct entry *next;   // Only used if collision at table[key]
} entry;

typedef struct {
  int size;
  entry **entries;
} table;

void bucket_append(entry *e, char *word, int key)
{
  entry *cur;
  cur = e;
  while (cur->next) cur = cur->next;
  cur->next = calloc(1, sizeof(entry));
  cur->next->val = word;
  cur->next->key = 1;
}

int get_key(char *word, int size)
{
  uint64_t key;
  int i, j;
  uint64_t tmp;
  int len = strlen(word);
  char bytes[4];

  if (len == 1) return word[0];

  key = 0;
  tmp = 0;
  for (i = 0; word[i] != '\0'; i++){
    bytes[i%4] = word[i];
    if ((i != 0 && (i+1) % 4 == 0) || i == len-1){
      int mult = 1;
      for (j = 0; j < strlen(bytes); j++){
        tmp += bytes[j] * mult;
        mult *= 256;
      }
      key += tmp;
      memset(bytes, 0, 4*sizeof(char));
    }
  }
  key = key % size;
  return key;
}

int hash(table *t, char *word)
{
  int key = get_key(word, t->size);

  if (t->entries[key]->val != NULL){
    bucket_append(t->entries[key], word, key);
    return 1;
  }

  t->entries[key]->val = word;
  t->entries[key]->key = 1;
  return 0;
}

int find(table *t, char *word)
{
  int key = get_key(word, t->size);
  char *found = t->entries[key]->val;
  entry *cur;

  if (strcmp(word, found) == 0){
    return 1;
  }

  cur = t->entries[key];
  while (cur->next){
    cur = cur->next;
    if (strcmp(word, cur->val) == 0){
      return 1;
    }
  }

  printf("Could not find %s in table\n", word);
  return 0;
}

table *table_init(int size)
{
  table *t;
  int i;
  t = calloc(1, sizeof(table));
  t->size = size;
  t->entries = calloc(t->size, sizeof(entry *));
  for (i = 0; i < t->size; i++) t->entries[i] = calloc(1, sizeof(entry));
  return t;
}

void table_free(table *t)
{
  int i;
  for (i = 0; i < t->size; i++){
    entry *cur = t->entries[i];
    entry *tmp;
    while (cur){
      tmp = cur;
      cur = cur->next;
      free(tmp);
    }
  }
  free(t->entries);
  free(t);
}

int main()
{
  int i;
  file2lines *f2l;
  table *t;

  f2l = file2lines_read(FILE_NAME);
  t = table_init(f2l->num_lines*2);

  printf("Adding entries to table...\n");
  for (i = 0; i < f2l->num_lines; i++)
    hash(t, f2l->lines[i]);
  printf("total added to table: %d\n", f2l->num_lines);

  printf("Performing hash map search...\n");
  int total = 0;
  for (i = 0; i < f2l->num_lines; i++)
    if (find(t, f2l->lines[i])) total++;
  printf("total found in table: %d\n", total);

  table_free(t);
  file2lines_free(f2l);
}
