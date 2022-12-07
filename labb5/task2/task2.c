#include <stdio.h>
#include <pthread.h>

struct thread_arg {
    char * name;
    char * str;
    int num;
};

void * my_func(void * args);

int main() {
    struct thread_arg targ1;
    pthread_t thread1;
    targ1.name = "thread1";
    targ1.str = "String for thread1.";
    targ1.num = 1;
    int result1 = pthread_create(&thread1, NULL, &my_func, &targ1);

    if(result1 != 0) {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    struct thread_arg targ2;
    pthread_t thread2;
    targ2.name = "thread2";
    targ2.str = "String for thread2.";
    targ2.num = 2;
    int result2 = pthread_create(&thread2, NULL, &my_func, &targ2);

    if(result2 != 0) {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    struct thread_arg targ3;
    pthread_t thread3;
    targ3.name = "thread3";
    targ3.str = "String for thread3.";
    targ3.num = 3;
    int result3 = pthread_create(&thread3, NULL, &my_func, &targ3);

    if(result3 != 0) {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    struct thread_arg targ4;
    pthread_t thread4;
    targ4.name = "thread4";
    targ4.str = "String for thread4.";
    targ4.num = 4;
    int result4 = pthread_create(&thread4, NULL, &my_func, &targ4);

    if(result4 != 0) {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    sleep(5);
    return 0;
}

void * my_func(void * args) {
    struct thread_arg targ = *(struct thread_arg *) args;

    for(int i = 0; i < targ.num; i++) {
        fprintf(stderr, "%s. %s %d\n", targ.name, targ.str, i+1);
    }

    return NULL;
}