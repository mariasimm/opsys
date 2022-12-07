#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "element.h"

struct m_elem {
    void * elem;
};

struct m_elem * element_create(){
    struct m_elem * res = malloc(sizeof(struct m_elem));
    if (!res) {
        fprintf(stderr, "Element Allocation Error\n");
    } else {
        res->elem = NULL;
    }
    return res;
}


bool element_set(struct m_elem * el, void * val, size_t size) {
    if (el->elem) {
        free(el->elem);
        el->elem = NULL;
    }
    el->elem = malloc(size);
	if (!el->elem) {
		fprintf(stderr, "Allocation memory error!!!\n");
		return false;
	}
	memcpy(el->elem, val, size);
	return true;
}

void * element_get(struct m_elem * el) {
    return el->elem;
}

void element_destroy(struct m_elem ** el) {
    free((*el)->elem);
	(*el)->elem = NULL;
	free(*el);
	(*el) = NULL;
}

void apply(struct m_elem * el, void (*f)(void * arg)) {
    f(el->elem);
}
