#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char TOKENS[18][80] = { "if", "while", "for", "else if", "else"
                              "{", "}", "(", ")", ".", ";", "#",
                              "int", "float", "double", "char", "bool" };

void lexer_tokenize(char* word)
{
	for (int i = 0; i < 18; i++){
		if (strcmp(TOKENS[i], word) == 0){
			return;
		}
	}
}

void lexer_scan(char* line, int n)
{
	if (n == 0) return;

	int index = 0;
	while (index != n){
		char word[80];
		char c = line[index];
		int i = 0;

		//ignore leading whitespace
		while (c == '\t' || c == ' '){
			index++;
			c = line[index];
		}

		//get current word
		while (c != '\n' && c != ' ' && c != '(' && c != '{'){
			if (c == '\t') continue;
			word[i] = c;
			index++;
			c = line[index];
			i++;
		}
		word[i] = '\0';
		printf("%s\n", word);

		lexer_tokenize(word);

		index++;
	}

	return;
}
