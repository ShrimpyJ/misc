/* 1-13: Prints histogram of lengths of words from input */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int c;
	int wc[1000];
	int nchars, nwords;
	int i, j;
	int max;

	nchars = nwords = max = 0;
	while ((c = getchar()) != EOF){
		if (c == ' ' || c == '\t' || c == '\n'){
			wc[nwords] = nchars;
			nwords++;
			if (nchars > max) max = nchars;
			nchars = 0;
		}
		else nchars++;
	}

	/* Print a vertical bar for each word */
	for (i = max; i > 0; i--){
		for (j = 0; j < nwords; j++){
			if (wc[j] >= i) printf("|");
			else printf(" ");
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");

	/* Print a horizontal bar for each word */
	for (i = 0; i < nwords; i++){
		printf("Word %d: ", i);
		for (j = 0; j < wc[i]; j++){
			printf("-");
		}
		printf("\n");
	}

	return 0;
}
