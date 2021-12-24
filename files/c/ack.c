#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int A(int m, int n)
{
  printf("m: %d   n: %d\n", m, n);
  if      (m == 0) return n+1;
  else if (n == 0) return A(m-1, 1);
  else             return A(m-1,A(m,n-1));
}

int main()
{
  A(4,4);
}
