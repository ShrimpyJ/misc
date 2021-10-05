#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	int i, j;
	int bullet;
	int p1, p2;
	int n;

	srand(time(0));

	p1 = p2 = 0;
	n = 500000;
	for (i = 0; i < n; i++){
		bullet = (rand() % 6) + 1;
		if (bullet % 2 == 0) p1++;
		else p2++;
	}

	printf("p1: %d\np2: %d\n", p1, p2);
	printf("p1: %0.2f%\np2: %0.2f%\n", (float)p1/n*100, (float)p2/n*100);

	return 0;
}
