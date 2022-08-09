#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TARGET 5
#define LENGTH 5

typedef struct pair
{
  char *word;
  long num;
} Pair;

typedef struct answer
{
  struct pair *p[TARGET];
  int nitems;
} Answer;

void pair_setnum(Pair *p)
{
  int i;
  int n;
  p->num = 0;
  for (i = 0; i < strlen(p->word); i++){
    n = p->word[i] - 97;
    p->num += pow(2, n);
  }
}

void set_pair(Pair *p, char *word)
{
  p->word = calloc(strlen(word), sizeof(char));
  strncpy(p->word, word, strlen(word));
  pair_setnum(p);
}

Answer *answer_init()
{
  Answer *a = calloc(1, sizeof(Answer));
  return a;
}

void answer_push(Answer *a, Pair *p)
{
//  printf("  Pushing %s\n", p->word);
  a->p[a->nitems] = p;
//  a->p[a->nitems] = calloc(1, sizeof(Pair *));
//  a->p[a->nitems]->word = calloc(strlen(p->word), sizeof(char));
//  strncpy(a->p[a->nitems]->word, p->word, strlen(p->word));
//  a->p[a->nitems]->num = p->num;
  a->nitems++;
}

void answer_pop(Answer *a)
{
  if (a->nitems <= 0){
//    printf("    Cannont pop, no items\n");
    return;
  }
//  printf("    Popping %s\n", a->p[a->nitems-1]->word);
  a->nitems--;
}

void answer_print(Answer *a)
{
  int i;
  for (i = 0; i < a->nitems; i++){
    printf("%s ", a->p[i]->word);
  }
  printf("\n");
}

void answer_free(Answer *a)
{
  int i;
  for (i = 0; i < a->nitems; i++){
    answer_pop(a);
//    free(a->p[i]->word);
//    free(a->p[i]);
  }
  free(a);
}

void lower(char *word)
{
  int i;
  for (i = 0; i < strlen(word); i++){
    if (word[i] >= 'A' && word[i] <= 'Z') word[i] += 32;
  }
}

/*
 * 00000000 00000000 00000000 00000000
 *       zy xwvutsrq ponmlkji hgfedcba
 */

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

int has_repeating(char *word)
{
  int i, j;
  for (i = 0; i < strlen(word); i++){
    for (j = i+1; j < strlen(word); j++){
      if (word[i] == word[j]) return 1;
    }
  }
  return 0;
}

int has_nonalpha(char *word)
{
  int i;
  for (i = 0; i < word[i]; i++){
    if (word[i] < 'A') return 1;
    if (word[i] > 'Z' && word[i] < 'a') return 1;
    if (word[i] >'z') return 1;
  }
  return 0;
}

int findValid(int index, int n, Pair *word, Pair **pairs, int npairs, Answer *answer)
{
  int i, j;
  int result;

  /* Base case: done when answer array contains enough pairs */
  if (answer->nitems == TARGET){
    printf("Answer found: ");
    answer_print(answer);
    return 1;
  }

  for (i = index; i < npairs; i++){
    /* If current word/answerlist contains no matching characters */
    result = n & pairs[i]->num;
    if (result == 0){
      /* Add answer to answerlist and recurse with new answerlist */
      answer_push(answer, pairs[i]);
      for (j = i; j < npairs; j++){
        findValid(j+1, n | pairs[i]->num, pairs[j], pairs, npairs, answer);
        break;
      }
      answer_pop(answer);
    }
  }

  return 0;
}

int main(int argc, char** argv)
{
	char **lines;
  char **words;
	FILE *f;
	int f_items;
  int i;
  int index;
  Pair **pairs;
  Answer *answer;

	if (argc != 2){
		fprintf(stderr, "Usage: trie INPUT_FILE\nInput file should be words delimited by newline\n");
		exit(1);
	}
	if ((f = fopen(argv[1], "r")) == 0){
		perror(argv[1]);
		exit(1);
	}

	/* Read file */
	lines = read_file(f, &f_items);
	fclose(f);

  /* Remove newlines from words */
  for (i = 0; i < f_items; i++){
    lines[i][strlen(lines[i])-1] = '\0';
  }

  /* Add valid lines to words array */
  words = calloc(f_items, sizeof(char *));
  index = 0;
  for (i = 0; i < f_items; i++){
    /* Get words of valid length which do not have symbols */
    if (strlen(lines[i]) == LENGTH && !has_repeating(lines[i]) && !has_nonalpha(lines[i])){
      lower(lines[i]);
      words[index] = calloc(strlen(lines[i]), sizeof(char));
      strncpy(words[index], lines[i], strlen(lines[i]));
      index++;
    }
  }

  /* Create pairs */
  pairs = calloc(index, sizeof(Pair *));
  for (i = 0; i < index; i++){
    pairs[i] = calloc(1, sizeof(Pair));
    pairs[i]->word = calloc(strlen(words[i]), sizeof(char));
    strncpy(pairs[i]->word, words[i], strlen(words[i]));
    pair_setnum(pairs[i]);
//    printf("%s %10d\n", pairs[i]->word, pairs[i]->num);
  }

  /* Free intermediate space */
//  for (i = 0; i < f_items; i++) free(lines[i]);
//  free(lines);
//  for (i = 0; i < index; i++) free(words[i]);
//  free(words);

  /* Find cliques, trying each word in the list */
  for (i = 0; i < index; i++){
    /* Init answer */
    printf("trying %s\n", pairs[i]->word);
    answer = answer_init();
    answer_push(answer, pairs[i]);

    findValid(i+1, pairs[i]->num, pairs[i], pairs, index, answer);
    answer->nitems = 0;
    free(answer);
  }
  printf("Done\n");

  /* Free pairs */
  for (i = 0; i < index; i++){
    free(pairs[i]->word);
    free(pairs[i]);
  }
  free(pairs);

	return 0;
}
