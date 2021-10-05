#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const char* WORD_FILE = "./hangman_games.txt";

const char* BOARD_0 =
"      ------\n\
      |    |\n\
           |\n\
           |\n\
           |\n\
           |\n\
           |\n\
           |\n\
    ========\n";
const char* BOARD_1 =
"      ------\n\
      |    |\n\
      O    |\n\
           |\n\
           |\n\
           |\n\
           |\n\
           |\n\
    ========\n";
const char* BOARD_2 =
"      ------\n\
      |    |\n\
      O    |\n\
      |    |\n\
      |    |\n\
           |\n\
           |\n\
           |\n\
    ========\n";
const char* BOARD_3 =
"      ------\n\
      |    |\n\
      O    |\n\
      |    |\n\
      |    |\n\
     /     |\n\
           |\n\
           |\n\
    ========\n";
const char* BOARD_4 =
"      ------\n\
      |    |\n\
      O    |\n\
      |    |\n\
      |    |\n\
     / \\   |\n\
           |\n\
           |\n\
    ========\n";
const char* BOARD_5 =
"      ------\n\
      |    |\n\
      O    |\n\
     /|    |\n\
      |    |\n\
     / \\   |\n\
           |\n\
           |\n\
    ========\n";
const char* BOARD_6 =
"      ------\n\
      |    |\n\
      x    |\n\
     /|\\   |\n\
      |    |\n\
     / \\   |\n\
           |\n\
 YOU LOSE  |\n\
    ========\n";

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
	ret = calloc(size+1, sizeof(char));
	token = strtok(str, "\n");
	i = 0;
	while (token != NULL){
		ret[i] = calloc(1, strlen(token)+50);
		token = strtok(NULL, "\n");
		if (!token) break;
		strcpy(ret[i], token);
		i++;
	}
	free(str);
	free(token);

	*f_items = i;

	return ret;
}

void get_board(int strikes)
{
	switch(strikes){
		case 0:
			printf(BOARD_0);
			break;
		case 1:
			printf(BOARD_1);
			break;
		case 2:
			printf(BOARD_2);
			break;
		case 3:
			printf(BOARD_3);
			break;
		case 4:
			printf(BOARD_4);
			break;
		case 5:
			printf(BOARD_5);
			break;
		case 6:
			printf(BOARD_6);
			break;
	}
}

int check_alphabet(char alphabet[], char c)
{
	int i;

	for (i = 0; i < 26; i++){
		if (alphabet[i] == c) return 1;
	}
	return 0;
}

int check_guess(char phrase[], char c)
{
	int i;
	int ret[strlen(phrase)];

	for (i = 0; i < strlen(phrase); i++){
		if (phrase[i] == c) return i;
	}
	return -1;
}

int check_victory(char uncovered[])
{
	int i;

	for (i = 0; i < strlen(uncovered); i++){
		if (uncovered[i] == '_') return 0;
	}
	return 1;
}

void print_info(int strikes, char alphabet[], char uncovered[])
{
	get_board(strikes);
	printf(alphabet);
	printf("\n");
	printf(uncovered);
}

int main(int argc, char** argv)
{
	FILE *fp;
	char **arr;
	int f_items;
	int r;
	char phrase[255];
	char uncovered[255];
	char alphabet[27];
	char input[99];
	char c;
	int strikes;
	int failure;
	int guesses;
	int i;
	int correct;
	int pass;

	srand(time(NULL));

	strikes = 0;
	failure = 6;
	guesses = 0;
	correct = 0;

	/* Read file into array of lines */
	if ((fp = fopen(WORD_FILE, "r")) == 0){
		perror(WORD_FILE);
		exit(1);
	}
	arr = read_file(fp, &f_items);
	fclose(fp);

	/* Select random line from file and use it as phrase */
	r = rand() % f_items;
	for (i = 0; i < strlen(arr[r]); i++){
		phrase[i] = arr[r][i];
	}
	phrase[i] = '\0';

	//printf("%s\n", phrase);

	/* Create alphabet empty at game start */
	for (i = 0; i < 26; i++){
		alphabet[i] = ' ';
	}
	alphabet[i] = '\n';
	alphabet[i+1] = '\0';

	/* Create uncovered phrase empty at game start */
	for (i = 0; i < strlen(phrase); i++){
		if (phrase[i] >= 'a' && phrase[i] <= 'z') uncovered[i] = '_';
		else if (phrase[i] >= 'A' && phrase[i] <= 'Z') uncovered[i] = '_';
		else uncovered[i] = phrase[i];
	}
	uncovered[i] = '\n';
	uncovered[i+1] = '\0';

	/* Game start */
	while (strikes != failure){
		print_info(strikes, alphabet, uncovered);

		while(1){    /* Get input and check that it's valid */
			fgets(input, 99, stdin);
			c = input[0];
			if (c < 97 || c > 123) printf("Invalid input. Enter a letter.\n");
			else if (strlen(input) > 2) printf("Invalid input. Enter a letter.\n");
			else if (check_alphabet(alphabet, c)) printf("You've already tried this letter.\n");
			else break;
		}

		alphabet[c-'a'] = c;

		pass = 0;
		for (i = 0; i < strlen(phrase); i++){
			if (phrase[i] == c || phrase[i]+32 == c){
				uncovered[i] = phrase[i];
				correct++;
				pass = 1;
			}
		}

		if (!pass) strikes++;
		guesses++;
		if (check_victory(uncovered)){
			print_info(strikes, alphabet, uncovered);
			printf("YOU WIN!!!\n");
			break;
		}
	}
	
	if (strikes == failure){
		print_info(strikes, alphabet, phrase);
	}

	printf("\n\n\nThanks for playing!\n");

	return 0;
}
