#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	n->children = realloc(n->children, sizeof(struct node*) * (n->num_children + 1));
	n->children[n->num_children] = new;
	n->num_children++;
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

	cur = malloc(sizeof(struct node));
	cur = T.head;
	for (i = 0; i < len; i++){
		memcpy(str, word, i+1);

		for (j = 0; j < cur->num_children; j++){
			if (strcmp(cur->children[j]->val, str) == 0) break;
		}

		if (j == cur->num_children) trie_add(cur, str, strlen(str));
		cur = cur->children[j];
	}

	return cur;
}

struct node *trie_find(struct trie T, char *word)
{
	int len;
	int i, j;
	char *str;
	int sublen;
	struct node *cur;

	len = strlen(word);
	/* Assemble word */
	str = calloc(len+2, sizeof(char));

	cur = malloc(sizeof(struct node));
	cur = T.head;
	for (i = 0; i < len; i++){
		strncpy(str, word, i+1);

		for (j = 0; j < cur->num_children; j++){
			if (strcmp(cur->children[j]->val, str) == 0) break;
		}

		if (j == cur->num_children){
			fprintf(stderr, "Error: could not find node '%s' in trie\n", word);
			exit(1);
		}
		cur = cur->children[j];
	}

	return cur;
}


char **read_file(FILE *f, int *f_items)
{
	char buffer[2];
	char *str;
	char *token;
	char **ret;
	int num_lines;
	int size;
	int i;

	/* Get size of file first */
	size = 0;
	while ((fread(&buffer, 1, 1, f)) != 0) size++;

	/* Create string of entire file to be delimited later */
	str = malloc(sizeof(char) * size + 4);
	i = num_lines = 0;
	fseek(f, 0, SEEK_SET);
	while ((fread(&buffer, 1, 1, f)) != 0){
		str[i] = buffer[0];
		if (str[i] == '\n') num_lines++;
		i++;
	}

	/* Delimit file by newline */
	ret = malloc(sizeof(char) * size + 4);
	memset(ret, 0, sizeof(ret));
	token = strtok(str, "\n");
	i = 0;
	while (token != NULL){
		ret[i] = malloc(sizeof(char) * strlen(token) + 1);
		token = strtok(NULL, "\n");
		memset(ret[i], 0, sizeof(ret[i]));
		if (!token) break;
		strcpy(ret[i], token);
		i++;
	}
	free(str);
	free(token);

	*f_items = i;

	return ret;
}

void trie_search(struct trie T, char **arr, int f_items)
{
	struct node *n;

	n = malloc(sizeof(struct node *));
	for (int i = 0; i < f_items; i++){
//		printf("Finding: %-33s", arr[i]);
		n = trie_find(T, arr[i]);
//		printf("Found: %s\n", n->val);
	}
}

char *linear_find(char **arr, int f_items, char *word)
{
	for (int i = 0; i < f_items; i++){
		if (strcmp(arr[i], word) == 0){
			return arr[i];
		}
	}
}

void linear_search(char **arr, int f_items)
{
	for (int i = 0; i < f_items; i++){
//		printf("%6d: Finding: %-33s", i, arr[i]);
		linear_find(arr, f_items, arr[i]);
	}
}

int main(int argc, char** argv)
{
	char **arr;
	FILE *f;
	struct trie T;
	int f_items;
	struct node *n;

	if (argc != 2){
		fprintf(stderr, "Usage: trie INPUT_FILE\nInput file should be words delimited by newline\n");
		exit(1);
	}
	if ((f = fopen(argv[1], "r")) == 0){
		perror(argv[1]);
		exit(1);
	}

	/* Read file */
	arr = read_file(f, &f_items);
	printf("items: %d\n", f_items);
	fclose(f);

	/* Create trie */
	T = trie_create();
	for (int i = 0; i < f_items; i++){
		trie_insert(T, arr[i]);
	}

	/* Search via trie */
	trie_search(T, arr, f_items);

	/* Search linearly */
//	linear_search(arr, f_items);

	/* Find word near end via trie */
//	printf("%s\n", trie_find(T, "zygote"));

	/* Find word near end linearly */
//	printf("%s\n", linear_find(arr, f_items, "zygote"));

	return 0;
}
