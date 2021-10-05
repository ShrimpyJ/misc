#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

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
		printf("Finding: %-33s", arr[i]);
		n = trie_find(T, arr[i]);
		printf("Found: %s\n", n->val);
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

	return 0;
}
