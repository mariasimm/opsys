#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <stddef.h>

#include "element.h"

void int_doubler(void * x) {
    *((int*)x) = 2 * *((int*)x);
}

void double_halfer(void * x) {
    *((double*)x) = *((double*)x) / 2.0;
}

int main(void) {
    printf("Test Element Example!\n");
    struct m_elem * elem = element_create();
    printf("address elem: %p, address data: %p\n", elem, element_get(elem));
    int x = 5;
    element_set(elem, &x, sizeof x);
    int *y = element_get(elem);
    printf("address elem: %p, address data: %p\n", elem, element_get(elem));
    printf("%d\n", *y);
    apply(elem, int_doubler);
    printf("address elem: %p, address data: %p\n", elem, element_get(elem));
    printf("%d\n", *y);


    double xx = 15.5;
    element_set(elem, &xx, sizeof xx);
    double *yy = element_get(elem);
    printf("address elem: %p, address data: %p\n", elem, element_get(elem));
    printf("%lf\n", *yy);
    apply(elem, double_halfer);
    printf("address elem: %p, address data: %p\n", elem, element_get(elem));
    printf("%lf\n", *yy);
    element_destroy(&elem);
    printf("address elem: %p\n", elem);

    return EXIT_SUCCESS;
}
