#include <stdlib.h>
#include <stdio.h>

int main()
{
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 60; j++){
			printf("%d %0 d\n", i+1, j);
		}
		getchar();
	}
}
