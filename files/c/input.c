#include <stdio.h>
#include <string.h>

int main()
{
	char input[99];
	int n;

	printf("Type some stuff: ");
	if (*fgets(input, 99, stdin) != '\n'){
	}
	else return -1;

	printf("Your input: %s\n", input);
}
