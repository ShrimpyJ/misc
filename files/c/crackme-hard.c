#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// *teateatajektjaetkajktjaektjeaktjaektjeljtklejkltjakl
// *teateatajektjaetkajktjaektjeaktjaektjeljtklejkltjakl
// *teateatajektjaetkajktjaektjeaktjaektjeljtklejkltjakl
// *teateatajektjaetkajktjaektjeaktjaektjeljtklejkltjakl
// *teateatajektjaetkajktjaektjeaktjaektjeljtklejkltjakl
// *teateatajektjaetkajktjaektjeaktjaektjeljtklejkltjakl

typedef enum {false, true} bool;

void get_pwd(char* pwd)
{
	char tmp[90];
	tmp[0] = 0x61;
	tmp[1] = 0x62;
	tmp[2] = 0x61;
	tmp[3] = 0x63;
	tmp[4] = 0x61;
	tmp[5] = 0x62;
	tmp[6] = 0x61;
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
	printf("%s\n", pwd);

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
