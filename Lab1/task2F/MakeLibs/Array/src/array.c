#include <stdlib.h>
#include <stdio.h>

#include "array.h"

struct array {
    struct m_elem ** array;
    size_t size;
};


struct array * array_create(size_t size) {
    struct array * res = malloc(sizeof (struct array));
    if (!res) {
        fprintf(stderr, "Array allocation error\n");
        return res;
    }
	res->size = size;
	res->array = (struct m_elem **)calloc(size, sizeof(struct m_elem*));
	if (!(res->array)) {
		fprintf(stderr, "Allocation Memory Error (inner buuffer)\n");
		return res;
	}
	return res;
}

size_t array_size(struct array * ar) {
    return ar->size;
}


bool array_element_set(struct array * ar, size_t ind, void * val, size_t size) {
    if (ind < ar->size) {
            if (!ar->array[ind]) ar->array[ind] = element_create();
        return element_set(ar->array[ind], val, size);
    }
	fprintf(stderr, "Index value error (index %d >= array size %d)!!!\n", (int)ind, (int)ar->size);
    return false;
}


void * array_element_get(struct array * ar, size_t ind) {
    if (ind < ar->size) {
        return element_get(ar->array[ind]);
    }
    return NULL;
}


void array_destroy(struct array ** el) {
    size_t i;
    for (i = 0; i < (*el)->size; i++) {
        if ((*el)->array[i]) element_destroy(((*el)->array+i));
    }
    free(*el);
    *el = NULL;
}


void map(struct array * el, void (*f)(void * arg)) {
    size_t i;
    for (i = 0; i < el->size; i++) {
        //f(element_get(el->array[i]));
        apply(el->array[i], f);
    }
}
