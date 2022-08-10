#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define vec3fill(n) (vec3){n, n, n}

typedef struct vec3
{
  double x, y, z;
} vec3;

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

int main()
{
  vec3 v = vec3_init(0, 0, 0);

  v = vec3_add(v, (vec3){3, 3, 3});
  vec3_print(v);
  v = vec3_sub(v, vec3fill(3));
  vec3_print(v);
}
