#ifndef TRIE_H
#define TRIE_H
typedef struct node{
	int depth;
	int num_children;
	struct node *parent;
	struct node **children;
	char *val;
	int visited;
} Node;

typedef struct trie{
	int num_layers;
	int num_items;
	struct node *head;
} Trie;

extern struct trie trie_create();
extern void trie_print(struct trie T);
extern struct node *trie_insert(struct trie T, const char *word);
extern struct node *trie_find(struct trie T, char *word);
extern void trie_destroy(struct trie T);

#endif
