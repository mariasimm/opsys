#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long *catalan_num;
int *prime_num;

struct thread_arg {
    int num;
};

#define NUM 10

void * my_func1(void * args);
long Cat(int n);
void * my_func2(void * args);
int isPrime(int n);

int main() {
    struct thread_arg targ1;
    pthread_t thread1;
    targ1.num = NUM;
    int result1 = pthread_create(&thread1, NULL, &my_func1, &targ1);

    if(result1 != 0) {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    if (pthread_join(thread1, NULL) != 0) {
        fprintf(stderr, "Join error\n");
        return 2;
    }

    fprintf(stderr, "\nAn array of catalan numbers: ");
    for(int i = 0; i < targ1.num; i++) {
        fprintf(stderr, "%ld ", catalan_num[i]);
    }
    fprintf(stderr, "\n");

    struct thread_arg targ2;
    pthread_t thread2;
    targ2.num = NUM;
    int result2 = pthread_create(&thread2, NULL, &my_func2, &targ2);

    if(result2 != 0) {
        fprintf(stderr, "Error!\n");
        return 1;
    }

    if (pthread_join(thread2, NULL) != 0) {
        fprintf(stderr, "Join error\n");
        return 2;
    }

    fprintf(stderr, "\nAn array of prime numbers: ");
    for(int i = 0; i < targ2.num; i++) {
        fprintf(stderr, "%d ", prime_num[i]);
    }
    fprintf(stderr, "\n");

    return 0;
}

void * my_func1(void * args) {
    struct thread_arg targ = *(struct thread_arg *) args;
    catalan_num = malloc(sizeof(long) * targ.num);
    for(int i = 0; i < targ.num; i++) {
        catalan_num[i] = Cat(i);
    }
    return NULL;
}

long Cat(int n) {
    int k;
    long s = 0;
    if (n < 2)
        return 1;
    for (k = 0; k < n; k ++)
        s += catalan_num[k] * catalan_num[n - 1 - k];
    return s;
}

void * my_func2(void * args) {
    struct thread_arg targ = *(struct thread_arg *) args;
    prime_num = malloc(sizeof(int) * targ.num);
    for(int i = 0, j = 0; i < targ.num; ) {
        if(isPrime(j)) {
            prime_num[i] = j;
            i++;
        }
        j++;
    }
    return NULL;
}

int isPrime(int n) {
    if (n > 1){
        for (int i = 2; i < n; i++)
            if (n % i == 0)
                return 0;
        return 1;
    }
    else
        return 0;
}
