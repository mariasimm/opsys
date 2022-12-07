#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <stddef.h>

#include "array.h"

void int_doubler(void * x) {
    *((int*)x) = 2 * *((int*)x);
}

void int_print(void * x) {
    printf("%5d", *((int*)x));
}

void double_print(void * x) {
    printf("%7.2lf", *((double*)x));
}

void double_halfer(void * x) {
    *((double*)x) = *((double*)x) / 2;
}

int main(void) {
    printf("Test Array Example!\n");
    struct array * arr = array_create(10);
    printf("Create array:\n");
    printf("address arr: %p, size: %d\n", arr, (int)array_size(arr));

    int x;
    size_t i;
    for (i = 0; i < array_size(arr); i++) {
        x = i;
        array_element_set(arr, i, &x, sizeof x);
    }
    printf("Initial int array:\n\t" );
    map(arr, int_print);
    printf("\n");


    int *y = array_element_get(arr, 3);
    printf("address of array item: %p, value of item: %d\n", y, *y);
    map(arr, int_doubler);
    printf("Changed array:\n\t" );
    map(arr, int_print);
    printf("\n");
    printf("address of array item: %p, value of item: %d\n", y, *y);
    x = -1;
    array_element_set(arr, 9, &x, sizeof x);
    printf("Next changed array:\n\t" );
    map(arr, int_print);
    printf("\n");


    double xx;
    for (i = 0; i < array_size(arr); i++) {
        xx = 3.3*i;
        array_element_set(arr, i, &xx, sizeof xx);
    }
    printf("Initial double array:\n\t" );
    map(arr, double_print);
    printf("\n");
    double *yy = array_element_get(arr, 3);
    printf("address of array item: %p, value of item: %lf\n", yy, *yy);
    map(arr, double_halfer);
    printf("Changed array:\n\t" );
    map(arr, double_print);
    printf("\n");
    printf("address of array item: %p, value of item: %lf\n", yy, *yy);
    xx = -1.1;
    array_element_set(arr, 9, &xx, sizeof xx);
    printf("Next changed array:\n\t" );
    map(arr, double_print);
    printf("\n");

    array_destroy(&arr);
    printf("Delete array\n");
    printf("address array: %p\n", arr);

    return EXIT_SUCCESS;
}
