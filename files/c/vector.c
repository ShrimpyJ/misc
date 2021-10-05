#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

int main(int argc, char** argv)
{
	vector* v = (vector*) malloc(sizeof(vector));
	vector_init(v);

	for (int i = 0; i < 36326; i++) vector_push_back(v, i*2);

	vector_print(v);

	vector_destroy(v);

	return 0;
}
