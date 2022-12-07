#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

struct thread_arg {
    int num;
    int *arr;
};

static void make_detached(struct thread_arg * arr);
void * threadFunc(void * args);
void * myFunc(void * args);
void * control(void * args);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "\nYou didn't enter the number\n");
        return 0;
    }

    int number = atoi(argv[1]);

    pthread_t thread;
    struct thread_arg targ;
    targ.num = number;
    targ.arr = malloc(sizeof(int) * targ.num);
    if(!targ.arr) {
        fprintf(stderr, "ERROR! %s\n", "Cannot Allocate Working Array");
        exit(1);
    }

    make_detached(&targ);

    srand(time(NULL));
    int result = pthread_create(&thread, NULL, &threadFunc, &targ);

    if(result != 0) {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    if (pthread_join(thread, NULL) != 0) {
        fprintf(stderr, "Join error\n");
        return 2;
    }

    fprintf(stderr, "\n\nFinal array\n");
    for(int i = 0; i < targ.num; i++) {
        fprintf(stderr, "[Main] [%d] %d\n", i, targ.arr[i]);
    }
}

void * threadFunc(void * args){
    struct thread_arg targ = *(struct thread_arg *) args;

    pthread_t *tid_arr;
    tid_arr = (pthread_t*)calloc(targ.num, sizeof(pthread_t));

    for(int i = 0; i < targ.num; i++) {
        struct thread_arg targs;
        targs.num = i;
        targs.arr = targ.arr;

        int result = pthread_create(tid_arr+i, NULL, &myFunc, &targs);

        if(result != 0) {
            fprintf(stderr, "[thread] Error!\n");
        }

        if (pthread_join(*(tid_arr+i), NULL) != 0) {
            fprintf(stderr, "[thread] Join error\n");
        }
    }
}

void * myFunc(void * args) {
    struct thread_arg targ = *(struct thread_arg *) args;

    fprintf(stderr, "\n[thread %d] sleeping for %d sec...", targ.num, targ.num);
    sleep(targ.num);

    int min = 1, max = 10;
    int number = rand()%(max - min) + 1;
    targ.arr[targ.num] = number;
    fprintf(stderr, "\n[generating number %d] %d\n\n", targ.num, targ.arr[targ.num]);

    fprintf(stderr, "\n[thread %d] sleeping for %d sec...", targ.num, number);
    sleep(number);
}

void * control(void * args){
    struct thread_arg targ = *(struct thread_arg *) args;
    int flag = 1;

    while(flag) {
        sleep(1);
        flag = 0;
        fprintf(stderr, "\n[control] Array for now\n");
        for(int i = 0; i < targ.num; i++) {
            fprintf(stderr, "[control] [%d] %d\n", i, targ.arr[i]);
            if(targ.arr[i] == 0)
                flag = 1;
        }
    }
}

static void make_detached(struct thread_arg * arr) {
    pthread_attr_t attr;
    pthread_t thread;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (pthread_create(&thread, &attr, &control, (void*)arr) != 0) {
        fprintf(stderr, "Error while Creation Detached Thread\n");
        exit(EXIT_FAILURE);
    }
    pthread_attr_destroy(&attr);
}
