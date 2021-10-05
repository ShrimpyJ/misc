/* Rainbow: Takes stdin (or a file using < on command line) and outputs text using
            a simple formula to print characters line-by-line, incrementing the number
            of spaces between the current char and previous by (the # of previous spaces)+1.
            New words always begin NEXT_WORD lines after the first char of the previous word.
            New sentences always begin the line after the previous sentence's last char. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN   100000    /* 100,000 character limit */
#define NEXT_WORD      4    /* Start printing next word every NEXT_WORD lines */

typedef struct word
{
	char *str;     /* Contents of the string */
	int len;       /* Length of the string */
	int c_index;   /* Index of letter within word */
	int index;     /* Index within array of words */
	int done;      /* Boolean: 0 for not done, 1 for done */
} Word;

int get_input(char** input)
{
	char word[MAX_LEN];
	char parsed[MAX_LEN];
	int len;
	int num_words;
	char *token;

	num_words = 0;
	fgets(word, MAX_LEN, stdin);
	len = strlen(word);
	strcpy(parsed, word);

	/* Get length of input */
	token = strtok(parsed, " ");
	while (token != NULL){
		len += strlen(token);
		token = strtok(NULL, " ");
		num_words++;
	}

	*input = malloc(sizeof(char) * len);

	/* Copy input to char** and get number of words */
	token = strtok(word, " ");
	while (token != NULL){
		strcat(*input, token);
		strcat(*input, "\n");
		token = strtok(NULL, " ");
	}
	free(token);

	return num_words;
}

void make_array(struct word ***w_arr, int num_words, char *input)
{
	char *token;
	int i;

	*w_arr = malloc(sizeof(Word) * num_words);

	token = strtok(input, "\n");
	for (i = 0; i < num_words; i++){
		(*w_arr)[i] = malloc(sizeof(Word));
		(*w_arr)[i]->len = strlen(token);
		(*w_arr)[i]->index = i;
		(*w_arr)[i]->done = 0;
		(*w_arr)[i]->c_index = 0;
		(*w_arr)[i]->str = malloc(sizeof(char) * (*w_arr)[i]->len);
		strcpy((*w_arr)[i]->str, token);

		token = strtok(NULL, "\n");
	}
	free(token);
}

int get_pos(int n)
{
	int i;
	int pos;

	pos = 0;
	for (i = 1; i <= n; i++){
		pos += i;
	}

	return pos;
}

void print_char(int pos, char c)
{
	int i;

	for (i = 0; i < pos; i++) printf(" ");
	printf("%c", c);
}

void find_words(struct word** w_arr, int arr_i, int cur_words, int **to_process)
{
	int i;
	int index;

	memset(to_process, 0, sizeof(to_process));
	*to_process = malloc(sizeof(int) * cur_words);

	/* Start with most recent word (arr_i) and work backwards.
	   If the word has already been printed, skip it and keep going back.
		 Otherwise, add the word to to_process. */
	i = 0;
	index = arr_i;
	while (i != cur_words){
		if (w_arr[index]->done){
			index--;
			continue;
		}
		(*to_process)[i] = index;
		index--;
		i++;
	}
}

void print(struct word*** w_arr, int arr_i, int cur_words, int num_words)
{
	int i, j, k;
	int *to_process;
	int index;
	int pos;
	int offset;
	int cur_words_copy;

	/* Repeat until no more words to process */
	while (cur_words != 0){

		/* Work in chunks, getting the words needing printing every loop */
		for (i = 0; i < NEXT_WORD; i++){
			offset = 0;

    /* Get array of words needing to be printed. Array is filled backwards,
		   so [0] will be the most recent word and the [n] will be the oldest */
			find_words(*w_arr, arr_i, cur_words, &to_process);
			cur_words_copy = cur_words;

			/* Find the pos to print each word and print its current char in that pos */
			for (k = 0; k < cur_words_copy; k++){
				index = (*w_arr)[to_process[k]]->c_index;
				pos = get_pos(index);
				print_char(pos-offset-k, (*w_arr)[to_process[k]]->str[index]);
				offset = pos;

				(*w_arr)[to_process[k]]->c_index++;

				/* Set a word to done when it has printed all letters (c_index==len) */
				if ((*w_arr)[to_process[k]]->c_index == (*w_arr)[to_process[k]]->len){
					(*w_arr)[to_process[k]]->done = 1;
					free((*w_arr)[to_process[k]]->str);
					free((*w_arr)[to_process[k]]);
					cur_words--;
				}
			}

			if (arr_i == num_words-1){
				printf("\n");
				break;
			}

			printf("\n");
		}

		/* If there's a next word, increment the array index and # of cur_words */
		if (arr_i+1 < num_words){
			arr_i++;
			cur_words++;
		}
	}
}

int main(int argc, char** argv)
{
	char *input;          /* Stdin */
	int len;              /* Total # of chars */
	int num_words;        /* Total # of words */
	int cur_words;        /* # of words currently being processed */
	struct word **w_arr;  /* Array of words */
	int arr_i;            /* For traversing array of words */
	int i;
	int line_count;

	num_words = get_input(&input);
	len = strlen(input);

	make_array(&w_arr, num_words, input);
	free(input);

	arr_i = line_count = 0;
	cur_words = 1;
	print(&w_arr, 0, cur_words, num_words);
	free(w_arr);

	return 0;
}
