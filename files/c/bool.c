#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char to_int(char *s)
{
	int i, j;
	int p;
	int len;
	int ret;

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

	if (ret > 255){
		fprintf(stderr, "error: number must be 0-255\n");
		exit(1);
	}

	return ret;
}

void check_bits(unsigned char n)
{
	unsigned char i;
	unsigned char bit;

	bit = 1;
	for (i = 0; i < 8; i++){
		if (n & bit) printf("bit %d: true\n", i);
		else printf("bit %d: false\n", i);
		bit *= 2;
	}
}

void print_bits(unsigned char n)
{
	unsigned char i;
	unsigned char bit;

	bit = 128;
	for (i = 0; i < 8; i++){
		if (n & bit) printf("1");
		else printf("0");
		bit = bit / 2;
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	unsigned char n;

	if (argc != 2){ fprintf(stderr, "usage: bool NUM\n"); exit(1); }

	n = to_int(argv[1]);

	printf("n: %d\n", n);

	check_bits(n);
	print_bits(n);

	return 0;
}
