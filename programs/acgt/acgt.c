#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
  int A_bound, T_bound, C_bound, G_bound;
  int AT, CG;
  int pid;
  struct timeval t;
  int r;
  int i;
  int iterations;
  double outlier_per, outlier;
  double AT_d, CG_d;
  const char *bases = "ACTG";
  char *ls, *rs;

  gettimeofday(&t, NULL);
  srand(t.tv_usec * t.tv_sec * pid);

  if (argc != 2){
    fprintf(stderr, "usage: acgt iterations\n");
    exit(1);
  }

  iterations = atoi(argv[1]);
  ls = calloc(iterations+3, sizeof(char));
  rs = calloc(iterations+3, sizeof(char));

  A_bound = 15;
  T_bound = A_bound * 2;
  C_bound = 100-(100-T_bound)/2;
  G_bound = 100;
  outlier_per = 0.15;
  outlier = A_bound*2 + A_bound*2*outlier_per;

  for (i = 0; i < iterations; i++){
    r = (rand() % 100) + 1;
    if      (r <= A_bound)                r = 0;
    else if (r > A_bound && r <= T_bound) r = 2;
    else if (r > T_bound && r <= C_bound) r = 1;
    else if (r > C_bound && r <= G_bound) r = 3;
    else{ fprintf(stderr, "error: invalid r value %d\n", r); exit(1); }
    ls[i] = bases[r];
    rs[i] = bases[(r+2)%4];
  }

  AT = CG = 0;
  for (i = 0; i < iterations; i++){
    if (ls[i] == 'A' || rs[i] == 'A') AT++;
    else CG++;
  }

  AT_d = (double) AT / iterations * 100.0;
  CG_d = (double) CG / iterations * 100.0;

  if (AT_d > outlier){
    printf("A/T: %.2lf percent\nC/G: %.2lf percent\n\n", AT_d, CG_d);
  }

  return 0;
}
