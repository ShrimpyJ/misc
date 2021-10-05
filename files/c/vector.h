#ifndef VECTOR
#define VECTOR
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

typedef struct dynamic_array
{
	int* data;
	size_t capacity;   //total capacity
	size_t size;       //elements in vector
} vector;

int vector_init(vector* v)
{
	v->data = (int*)malloc(sizeof(int));
	if (!v->data) return -1;

	v->size = 0;
	v->capacity = 1;

	return 0;
}

int vector_size(vector* v)
{
	return v->size;
}

int vector_capacity(vector* v)
{
	return v->capacity;
}

int vector_push_back(vector* v, int element)
{
	if (v->size == v->capacity){
		v->data = (int*)realloc(v->data, v->capacity*2*sizeof(int));
		if (v->data == NULL){
			printf("Error reallocating memory for vector_push_back\n");
			exit(1);
		}

		v->capacity *= 2;
		for (size_t i = v->size; i < v->capacity; i++) v->data[i] = 0;
	}

	v->data[v->size] = element;
	v->size++;

	return 0;
}

int vector_pop_back(vector* v)
{
	if (v->size == 0) return -1;

	v->data[v->size] = 0;
	v->size--;

	return 0;
}

int vector_clear(vector* v)
{
	if (v->size == 0) return -1;

	for (size_t i = v->size; i > 0; i--){
		v->data[v->size] = 0;
		v->size--;
	}

	return 0;
}

int vector_erase(vector* v, int element, ...)
{
	va_list args;
	va_start (args, element);
	int n = va_arg(args, int);
	va_end(args);
	if (n == v->size) n = 0;

	if (element < 0 || element > v->size) return -1;
	if (element+n > v->size) return -1;

	for (size_t i = element; i+n < v->size; i++) v->data[i] = v->data[i+n+1];

	v->size -= n;
	v->size--;

	for (size_t i = v->size; i < v->capacity; i++) v->data[i] = 0;

	return 0;
}

int vector_resize(vector* v, size_t n, int x)
{
	if (n == v->size) return -1;

	if (n < v->size){
		vector_erase(v, n, v->size-n-1);
		v->capacity = n;
		return 0;
	}

	if (n > v->capacity){
		v->data = realloc(v->data, (v->size+n)*sizeof(int));
		v->capacity = n;
		for (size_t i = v->size; i < v->capacity; i++) v->data[i] = x;
		v->size = n;

		return 0;
	}

	if (n > v->size){
		v->capacity = n;
		for (size_t i = v->size; i < v->capacity; i++){
			v->data[i] = x;
			v->size++;
		}
	}

	return 0;
}

void vector_print(vector* v)
{
	printf("Capacity: %ld\n", v->capacity);
	printf("    Size: %ld\n", v->size);
	for (size_t i = 0; i < v->size; i++) printf("%d ", v->data[i]);
	printf("\n");
}

void vector_destroy(vector *v)
{
	free(v->data);
	free(v);
}

#endif
