#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include "element.h"
#include <stdbool.h>
#include <stddef.h>

struct array;

struct array * array_create(size_t size);
size_t array_size(struct array * ar);
bool array_element_set(struct array * ar, size_t ind, void * val, size_t size);
void * array_element_get(struct array * ar, size_t ind);
void array_destroy(struct array ** el);
void map(struct array * el, void (*f)(void * arg));

#endif // ARRAY_H_INCLUDED
