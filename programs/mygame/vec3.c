#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vec3.h"

#define vec3fill(n) (vec3){n, n, n}

double dot_prod(vec3 a, vec3 b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec3_init(double x, double y, double z)
{
  vec3 v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

vec3 vec3_add(vec3 a, vec3 b)
{
  return (vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

vec3 vec3_sub(vec3 a, vec3 b)
{
  return (vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

vec3 vec3_mult(vec3 a, vec3 b)
{
  vec3 out;
  out.x = a.y * b.z - a.z * b.y;
  out.y = -a.x * b.z + a.z * b.x;
  out.z = a.x * b.y - a.y * b.x;
  return out;
}

double vec3_norm(vec3 a)
{
  return sqrt(dot_prod(a, a));
}

void vec3_print(vec3 v)
{
  printf("(%lf, %lf, %lf)\n", v.x, v.y, v.z);
}
