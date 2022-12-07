#include <stdio.h>
#include <pthread.h>
#include <time.h>

struct thread_arg {
    int num;
};

struct thread_args {
    int num;
    int minimum;
    int maximum;
    int stop_number;
};

void * my_func1(void * args);
void * my_func2(void * args);

int main() {
    struct thread_arg targ1;
    pthread_t thread1;
    targ1.num = 5;
    int result1 = pthread_create(&thread1, NULL, &my_func1, &targ1);

    if(result1 != 0) {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    if (pthread_join(thread1, NULL) != 0) {
        fprintf(stderr, "Join error\n");
        return 2;

    }

    srand(time(NULL));
    struct thread_args targ2;
    pthread_t thread2;
    targ2.num = 10;
    targ2.minimum = 1;
    targ2.maximum = 20;
    targ2.stop_number = rand()%(targ2.maximum - targ2.minimum + 1);
    int result2 = pthread_create(&thread2, NULL, &my_func2, &targ2);

    if(result2 != 0) {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    if (pthread_join(thread2, NULL) != 0) {
        fprintf(stderr, "Join error\n");
        return 2;

    }

    fprintf(stderr, "\nAll the children have finished their work\n");
    return 0;
}

void * my_func1(void * args) {
    struct thread_arg targ = *(struct thread_arg *) args;

    for(int i = 0; i < targ.num; i++) {
        fprintf(stderr, "Child Thread. Iteration №%d\n", i+1);
    }

    return NULL;
}

void * my_func2(void * args) {
    struct thread_args targ = *(struct thread_args *) args;

    fprintf(stderr, "%d - this number can stop the thread earlier\n", targ.stop_number);

    for(int i = 0; i < targ.num; i++) {
        int number = rand()%(targ.maximum - targ.minimum + 1);
        fprintf(stderr, "Child Thread 2. Iteration №%d. Random number: %d\n", i+1, number);
        if(number == targ.stop_number) {
            fprintf(stderr, "%d - this number stops the thread...\n", number);
            return NULL;
        }
    }

    return NULL;
}