#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000000

void vector_add()
{
  __m256i first = _mm256_set_epi32(0, 10, 20, 30, 40, 50, 60, 70);
  __m256i second = _mm256_set_epi32(1, 1, 1, 1, 1, 1, 1, 1);
  __m256i result = _mm256_add_epi32(first, second);

  int *values = (int *) &result;

  for (int i = 0; i < MAX; i++){
    for (unsigned short j = 0; j < 8; j++){
    }
    result = _mm256_add_epi32(result, second);
  }
}

void serial_add()
{
  int first[8] = {70, 60, 50, 40, 30, 20, 10, 0};
  int second[8] = {1, 1, 1, 1, 1, 1, 1, 1};

  for (int i = 0; i < MAX; i++){
    for (int j = 0; j < 8; j++){
      first[j] += second[j];
    }
  }
}

int main(int argc, char **argv)
{
  vector_add();
//  serial_add();
}
