#ifndef VEC3_H
#define VEC3_H

#define vec3fill(n) (vec3){n, n, n}

typedef struct vec3
{
  double x, y, z;
} vec3;

double dot_prod(vec3 a, vec3 b);
vec3 vec3_init(double x, double y, double z);
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_mult(vec3 a, vec3 b);
double vec3_norm(vec3 a);
void vec3_print(vec3 v);

#endif
