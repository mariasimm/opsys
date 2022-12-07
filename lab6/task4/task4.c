#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

double resultPi;

void * threadFunc(void * args);

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
    else {
        fprintf(stderr, "[main] The thread was finished usually\n");
        fprintf(stderr, "[main] Final number: %.20f\n", resultPi);
    }

}

void * threadFunc(void * args){
    int i = 0;

    if(pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL) != 0) {
        fprintf(stderr, "[thread] Cannot change cancel type\n");
        exit(EXIT_FAILURE);
    }

    int count = 100000, count1;
    double pi, a, b;

    fprintf(stderr, "\n%s  %s", "Approximation", "Number PI\n");

    int old_cancelled_state;
    for (count, count1 = 1; count != 0; count--, count1++) {
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancelled_state);
        if (count1 == 1) {
            a = 4 - 1;
            b = 1;
            pi = 4 / b - 4 / a;
            fprintf(stderr, "%d              %.20f\n", count1, pi);
        }
        if (count1 > 1) {
            a = a + 4;
            b = b + 4;
            pi = pi + (4 / b - 4 / a);
            fprintf(stderr, "%d              %.20f\n", count1, pi);
        }
        pthread_setcancelstate(old_cancelled_state, NULL);
        pthread_testcancel();
    }
    resultPi = pi;
    return NULL;
}
