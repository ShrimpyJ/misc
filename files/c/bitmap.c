//bitmap.c: print all combinations of a bitmap of size SIDE*SIDE
//          this will not reasonably finish at numbers higher than 5

#include <stdio.h>
#include <stdlib.h>

const int SIDE = 8;       //size of square's sides

//print a square by comparing the given number to each single bit
//i.e. 0001 then 0010 then 0100 then 1000
void print(int n)
{
	unsigned long count = 1;
	for (int i = 0; i < SIDE*SIDE; i++){
		if (i != 0 && i % SIDE == 0) printf("\n");

		if (count & n) printf("#");
		else printf("_");

		count = count << 1;
	}
	printf("\n\n");
}

int main(int argc, char** argv)
{
	if (SIDE > 8) exit(1);

	//get max value (2^(SIDE*SIDE))
	unsigned long max = 1;
	int square = SIDE*SIDE;
	if (SIDE == 8) square -= 1;

	for (int i = 0; i < square; i++){
		max = max << 1;
	}

	//iterate from 0 to max, printing square each time
	for (unsigned long i = 0; i < max; i++){
		printf("%lu\n", i);
		print(i);
	}

}
