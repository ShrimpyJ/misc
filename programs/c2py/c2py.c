#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int main(int argc, char** argv)
{
	if (argc != 2){
		printf("Error: need exactly two arguments\n");
		return 1;
	}

	FILE *cfile;
	if ((cfile = fopen(argv[1], "r")) == NULL){
		printf("Error: File does not exist\n");
		return 1;
	}

	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	while ((read = getline(&line, &len, cfile)) != -1){
		printf("LEXER WORKING ON:    %s", line);
		lexer_scan(line, strlen(line));
	}
	
	fclose(cfile);


	return 0;
}
