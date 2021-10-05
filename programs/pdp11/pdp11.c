#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.h"

#define EXIT_CODE    "EXIT"

void to_uppercase(char **input)
{
	int i;
	int len;
	char c;

	len = strlen(*input);
	if ((*input)[len-1] == '\n') (*input)[len-1] = '\0';
	for (i = 0; i < len; i++){
		c = (*input)[i];
		if (c >= 'a' && c <= 'z') (*input)[i] = c - ' ';
		else if (c >= 'A'&& c <= 'Z' || (c == '\0')){
		}
	}
}

void skip_whitespace(char *input, int *i)
{
	while (input[*i] == ' ' || input[*i] == '\t') (*i)++;
}

char *copy_arg(char *input, int index)
{
	int i, j;
	char *ret;

	ret = calloc(8, sizeof(char));
	i = index;
	j = 0;
	while(input[i] != ' ' && input[i] != '\t' && input[i] != '\0' && input[i] != ','){
		ret[j] = input[i];
		j++;
		i++;
	}

	return ret;
}

void free_args(char **args, int argc)
{
	int i;

	for (i = 0; i < argc; i++) free(args[i]);
	free(args);
}

char **get_args(char *input, int argc)
{
	char **ret;
	int len;
	int i, j;
	int index;

	ret = calloc(argc, sizeof(char *));

	/* Move past the opcode since it's not needed */
	len = strlen(input);
	i = 0;
	while(input[i] != ' ' && input[i] != '\t' && input[i] != '\0') i++;
	if (input[i] == '\0') return NULL;

	/* Move past any whitespace between the opcode and the first arg */
	skip_whitespace(input, &i);

	/* Copy the necessary number of args to the return array */
	index = 0;
	for (index = 0; index < argc; index++){
		ret[index] = copy_arg(input, i);
		if (strlen(ret[index]) == 0) return NULL;
		printf("str: '%s'\n", ret[index]);
		i += strlen(ret[index])+1;
		skip_whitespace(input, &i);
	}

	/* Make sure there's no args specified after the necessary number of args */
	if (input[i] != '\0' || input[i-1] == ',') return NULL;

	return ret;
}

void opcode_handle(char *input, struct opcode *o)
{
	char **args;
	int argc;

	/* Gather all arguments supplied */
	switch(o->type){
		case SINGLE:
			argc = 1;
			if ((args = get_args(input, argc)) == NULL){
				fprintf(stderr, "error: wrong # of args for %s (should be %d)\n", o->name, argc);
				return;
			}
			break;

		case DOUBLE:
			argc = 2;
			if ((args = get_args(input, argc)) == NULL){
				fprintf(stderr, "error: wrong # of args for %s (should be %d)\n", o->name, argc);
				return;
			}
			break;

		case BRANCH:
			argc = 0;
			break;

		case JUMP:
			argc = 1;
			if ((args = get_args(input, argc)) == NULL){
				fprintf(stderr, "error: wrong # of args for %s (should be %d)\n", o->name, argc);
				return;
			}
			break;

		case RET:
			switch(o->index){
				case 45 ... 46:
					argc = 1;
					if ((args = get_args(input, argc)) == NULL){
						fprintf(stderr, "error: wrong # of args for %s (should be %d)\n", o->name, argc);
						return;
					}
					break;
				case 47:
					argc = 2;
					if ((args = get_args(input, argc)) == NULL){
						fprintf(stderr, "error: wrong # of args for %s (should be %d)\n", o->name, argc);
						return;
					}
					break;
			}
			break;

		case TRAP:
			argc = 0;
			break;

		case MISC:
			switch(o->index){
				case 52 ... 55:
					argc = 0;
					break;
				case 56 ... 60:
					argc = 1;
					if ((args = get_args(input, argc)) == NULL){
						fprintf(stderr, "error: wrong # of args for %s (should be %d)\n", o->name, argc);
						return;
					}
					break;
			}
			break;

		case COND:
			argc = 0;
			break;
	}

	/* Check for argument accuracy */
	int i;
	for (i = 0; i < argc; i++) printf("arg [%d]: '%s'\n", i, args[i]);

	if (argc > 0) free_args(args, argc);
}

int main(int argc, char** argv)
{
	struct opcode **ops;  /* List of all 71 opcodes with their type, name, and octal representation */
	struct opcode *o;
	char *input;
	int type;

	ops = opcode_init();

	opcode_print_all(ops);

	input = calloc(99, sizeof(char));
	while(*fgets(input, 99, stdin)){
		to_uppercase(&input);
		if (strncmp(input, EXIT_CODE, 4) == 0) break;

		printf("You input: '%s'\n", input);
		if ((o = opcode_check(input, ops)) == NULL) continue;

		opcode_print(o);
		opcode_handle(input, o);
		opcode_free(o);
	}

	opcode_free_all(ops);
	free(input);

	return 0;
}
