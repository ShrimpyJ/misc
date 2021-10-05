#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NUM_ELEMENTS      5
#define MAX_DEGREE        3

typedef struct node
{
	int is_leaf;         /* Determines if leaf or node */

	struct node *next;   /* Only for leaves */
	void *data;

	int key;             /* Only for nodes */
	struct node **children;
} Node;

typedef struct btree
{
	struct node *root;
	int elements;
} Btree;

Btree btree_create()
{
	Btree ret;
	Node *root;
	root = malloc(sizeof(Node));
	root->key = 0;
	root->is_leaf = 1;
	ret.root = root;
	return ret;
}

Node btree_search(Node *n, int val)
{
	/* If node is a leaf, return node */

	/* If val <= k_0, return btree_search(k, p_0) */

}

Btree btree_insert(Btree b, int val)
{
	Node index;

	printf("Inserting %d\n", val);
	btree_search(b.root, 1);
}

int main(int argc, char **argv)
{
	Btree b;
	int i;

	b = btree_create();
	printf("Btree created with root key: %d\n", b.root->key);

	btree_insert(b, 1);

	for (i = 0; i < NUM_ELEMENTS; i++){
	}

	return 0;
}
