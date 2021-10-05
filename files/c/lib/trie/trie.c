#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

struct trie trie_create()
{
	struct trie T;
	struct node *head;

	head = malloc(sizeof(struct node));
	head->depth = 0;
	head->num_children = 0;
	head->visited = 0;
	head->parent = NULL;
	head->children = NULL;
	head->val = NULL;

	T.num_layers = 0;
	T.num_items = 0;
	T.head = head;

	return T;
}

void trie_print(struct trie T)
{
	int i;
	int items;
	struct node *tmp;
	struct node **q;

	q = malloc(sizeof(struct node *));
	q[0] = T.head;

	items = 1;
	tmp = malloc(sizeof(struct node *));
	while(q){
		tmp = q[0];
		items--;
		q = realloc((void *) q, tmp->num_children + items);
		for (i = 0; i < tmp->num_children; i++){
		}
	}
}

struct node *trie_new(struct node *n, char *word, int len)
{
	struct node *new;
	new = malloc(sizeof(struct node));
	new->depth = len;
	new->num_children = 0;
	new->parent = n;
	new->children = NULL;
	new->val = malloc(sizeof(char) * len + 1);
	new->visited = 0;
	strcpy(new->val, word);
	return new;
}

struct node *trie_add(struct node *n, char *word, int len)
{
	struct node *new;
	new = trie_new(n, word, len);
	n->children = realloc(n->children, sizeof(struct node*) * (n->num_children+3));
	n->children[n->num_children] = new;
	n->num_children++;
	return n;
}

struct node *trie_insert(struct trie T, const char *word)
{
	int len;
	int i, j;
	char *str;
	struct node *cur;

	len = strlen(word);

	/* Assemble word */
	str = calloc(len+2, sizeof(char));

	cur = T.head;
	for (i = 0; i < len; i++){
		memcpy(str, word, i+1);

		for (j = 0; j < cur->num_children; j++){
			if (strcmp(cur->children[j]->val, str) == 0) break;
		}

		if (j == cur->num_children) trie_add(cur, str, strlen(str));
		cur = cur->children[j];
	}
	free(str);

	return cur;
}

struct node *trie_find(struct trie T, char *word)
{
	int len;
	int i, j;
	char *str;
	struct node *cur;

	len = strlen(word);

	/* Assemble word */
	str = calloc(len+2, sizeof(char));

	cur = T.head;
	for (i = 0; i < len; i++){
		strncpy(str, word, i+1);

		for (j = 0; j < cur->num_children; j++){
			if (strcmp(cur->children[j]->val, str) == 0) break;
		}

		if (j == cur->num_children){
			return NULL;
		}
		cur = cur->children[j];
	}
	free(str);

	return cur;
}

void trie_destroy_node(struct node *n)
{
	int i;
	
	for (i = 0; i < n->num_children; i++){
		trie_destroy_node(n->children[i]);
	}
	free(n->val);
	free(n->children);
	free(n);
}

void trie_destroy(struct trie T)
{
	trie_destroy_node(T.head);
}
