#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

void get_pwd(char* pwd)
{
	char* tmp;
	tmp = "abacaba";
	strcpy(pwd, tmp);
}

void print_message()
{
	printf("Enter code: ");
}

void get_input(char* str)
{
	scanf("%s", str);
}

bool check_code(char* str, char* pwd)
{
	if (strlen(str) != strlen(pwd)) return false;
	if (strcmp(str, pwd) != 0) return false;
	return true;
}

void welcome()
{
	printf("Welcome, Agent...\n");
}

int main()
{
	char pwd[90];
	get_pwd(pwd);

	bool b = false;
	int attempts = 9;
	while (!b && attempts != 0){
		print_message();
		char str[90];
		get_input(str);
		check_code(str, pwd);
		b = check_code(str, pwd);
		if (!b){
			attempts--;
			printf("ERROR. YOU HAVE %d ATTEMPTS REMAINING\n", attempts);
		}
		else welcome();
	}

	if (attempts == 0) printf("TOO MANY FAILED ATTEMPTS. EXITING...\n");

	return 0;
}
