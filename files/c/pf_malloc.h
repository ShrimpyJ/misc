#ifndef PF_MALLOC_H
#define PF_MALLOC_H

#include <stddef.h>
#include <stdbool.h>

bool  pf_malloc_init(void *slab, size_t size);
void *pf_malloc     (void *slab, size_t size);
void  pf_free       (void *slab, void *ptr);

void *pf_metamalloc_init   (size_t size);
void  pf_metamalloc_destroy(void *meta);
int   pf_metamalloc        (void *meta, size_t size);
int   pf_metamemalign      (void *meta, size_t alignment, size_t size);
void  pf_metafree          (void *meta, size_t offset);

#endif
