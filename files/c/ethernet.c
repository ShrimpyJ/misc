#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct machine{
  uint64_t mac;
} Machine;

typedef struct domain{
  int num_machines;
  Machine **machines;
} Domain;
