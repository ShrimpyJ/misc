#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint32_t to_int(char *s)
{
	int i, j;
	int p;
	int len;
	uint32_t ret;

	len = strlen(s);
	ret = 0;
	for (i = 0; i < len; i++){
		if (s[i] >= '0' && s[i] <= '9'){
			p = 1;
			for (j = 0; j < len-1-i; j++) p *= 10;
			ret += p * (s[i] - '0');
		}
		else{
			fprintf(stderr, "error: number contains invalid character %c\n", s[i]);
			exit(1);
		}
	}

	return ret;
}

void print_bits(uint32_t n)
{
	int i;
	uint32_t bit;

	bit = 1;
	for (i = 0; i < 31; i++) bit *= 2;

	for (i = 0; i < 32; i++){
		if (i != 0 && i % 8 == 0) printf(" ");
		n & bit ? printf("1") : printf("0");
		bit = bit / 2;
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	uint32_t n;

	if (argc != 2){ fprintf(stderr, "usage: bool NUM\n"); exit(1); }

	n = to_int(argv[1]);

	print_bits(n);

	return 0;
}
