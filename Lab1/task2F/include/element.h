#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include <stdbool.h>
#include <stdbool.h>
#include <stddef.h>

struct m_elem;

struct m_elem * element_create();
bool element_set(struct m_elem * el, void * val, size_t size);
void * element_get(struct m_elem * el);
void element_destroy(struct m_elem ** el);
void apply(struct m_elem * el, void (*f)(void * arg));

#endif // ELEMENT_H_INCLUDED
