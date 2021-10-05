#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef void (*printer_t) (int);

void print_to_n(int n)
{
	int i;
	for (i = 0; i < n; i++) printf("%d\n", i);
}

void print_n(int n)
{
	printf("%d\n", n);
}

void print_caller(printer_t printer, int n)
{
	printer(n);
}

int main(int argc, char** argv)
{
	printer_t p;

	p = &print_to_n;
	print_caller(p, 15);

	return 0;
}
