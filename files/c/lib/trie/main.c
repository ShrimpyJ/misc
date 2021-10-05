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
	int len;

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
	ret = (char **) calloc(num_lines+1, sizeof(char*));
	i = 0;
	token = strtok(str, "\n");
	len = strlen(token);
	while (token != NULL){
		len = strlen(token);
		ret[i] = (char *) calloc(len, sizeof(char));
		memcpy(ret[i], token, len);
		token = strtok(NULL, "\n");
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
	fclose(f);

	/* Create trie */
	T = trie_create();
	for (int i = 0; i < f_items; i++){
		trie_insert(T, arr[i]);
	}

	/* Search via trie */
	//trie_search(T, arr, f_items);
	char input[100];
	while(1){
		printf("Enter word: ");
		fgets(input, 100, stdin);
		input[strcspn(input, "\r\n")] = 0;
		if (trie_find(T, input)) printf("Found %s\n", input);
		else printf("Could not find %s\n", input);
	}

	/* Free */
	for (int i = 0; i < f_items+1; i++) free(arr[i]);
	free (arr);
	trie_destroy(T);

	return 0;
}
