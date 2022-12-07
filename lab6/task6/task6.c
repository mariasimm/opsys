#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void * threadFunc(void * args);
void finalize(void * arg);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "\n[main] You didn't enter the number\n");
        return 0;
    }

    int sec = atoi(argv[1]);

    pthread_t thread;
    int result = pthread_create(&thread, NULL, &threadFunc, NULL);

    if(result != 0) {
        fprintf(stderr, "[main] Error!\n");
        return 1;
    }

    sleep(sec);
    printf("[main] Send cancel command to thread %u\n", (unsigned int)thread);
    pthread_cancel(thread);

    void* iscanceled;

    if (pthread_join(thread, &iscanceled) != 0) {
        fprintf(stderr, "[main] Join error\n");
        return 2;
    }

    if (iscanceled == PTHREAD_CANCELED)
        fprintf(stderr, "[main] The thread was really cancelled\n");
    else
        fprintf(stderr, "[main] The thread was finished usually\n");

}

void * threadFunc(void * args){
    int i = 0;
    int *arr = &i;

    pthread_cleanup_push(finalize, arr);

    if(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL) != 0) {
        fprintf(stderr, "[thread] Cannot change cancel type\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        fprintf(stderr, "[thread] Iteration №%d\n", ++i);
        sleep(1);
    }

    pthread_cleanup_pop(1);

}

void finalize(void * arg) {
    int num = *((int*)arg);
    fprintf(stderr,"Thread finalizer tid(%u).\n\tFinal number %d\n",
           (unsigned int)pthread_self(), num);
}
