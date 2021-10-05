#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef enum {false, true} bool;

void get_pwd(int *p[], int* x, int* y, int* z, int* t, int* f, int* g, int* h)
{
//	int *p = malloc(7*sizeof(*p));;
	*p = h;
	*(p+1) = f;
	*(p+2) = g;
	*(p+3) = x;
	*(p+4) = z;
	*(p+5) = y;
	*(p+6) = t;
//	return p;
}

void print_message()
{
	printf("Enter code: ");
}

void get_input(char* str)
{
	scanf("%s", str);
}

bool check_code(char* str, int **index)
{
	int size = 7;
	if (strlen(str) != size) return false;
	for (int i = 0; i < size; i++){
		int n = str[i];
		if (n != *index[i]) return false;
	}
	return true;
}

void welcome()
{
	printf("Welcome, Agent...\n");
}

int main()
{
	int x = 99, y = 98, z = 97, t = 97, f = 98, g = 97, h = 97;
	int *p[7];
	get_pwd(p,&x,&y,&z,&t,&f,&g,&h);

	bool b = false;
	int attempts = 9;
	while (!b && attempts != 0){
		print_message();
		char str[90];
		get_input(str);

		b = check_code(str,p);
		if (!b){
			attempts--;
			printf("ERROR. YOU HAVE %d ATTEMPTS REMAINING\n", attempts);
		}
		else welcome();
	}

	if (attempts == 0) printf("TOO MANY FAILED ATTEMPTS. EXITING...\n");

	return 0;
}
