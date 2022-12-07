#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define SEC 1

void * my_func(void * args);

int main() {
    pthread_t thread;
    int result = pthread_create(&thread, NULL, &my_func, NULL);

    if(result != 0) {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        fprintf(stderr, "Main Thread. Iteration №%d\n", i+1);
        sleep(SEC);
    }

    return 0;
}

void * my_func(void * args) {
    for(int i = 0; i < 10; i++) {
        fprintf(stderr, "Child Thread. Iteration №%d\n", i+1);
        sleep(SEC);
    }

    return NULL;
}