#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define STR_MAX_LEN 256

static pthread_key_t str_key;

void * myFunc(void * args);
char *strConstr(char *string);

int main(int argc, char *argv[]){
    if (argc == 1) {
        fprintf(stderr, "\n[main] You didn't enter the number\n");
        return 0;
    }

    srand(time(NULL));

    int amount = atoi(argv[1]);
    pthread_t tid_arr [amount];

    static pthread_once_t once = PTHREAD_ONCE_INIT;


    for(int i = 0; i < amount; i++) {
        fprintf(stderr, "[main] Thread %d started!\n", i);
        if(pthread_create(tid_arr+i, NULL, &myFunc, "basic text. rand number") != 0) {
            fprintf(stderr, "[main] Error!\n");
        }
    }

    for(int i = 0; i < amount; i++) {
        if (pthread_join(*(tid_arr+i), NULL) != 0) {
            fprintf(stderr, "[main] Join error\n");
        }
        sleep(1);
    }

}

void * myFunc(void * args) {
    char * str = (char *)args;

    int num = rand()%(5-1);

    for(int i = 0; i < num; i++) {
        int random = rand()%(10-1);
        printf("tid(%u), str: %s %d\n", (unsigned int) pthread_self(), strConstr(str), random);
    }

    return NULL;
}

static void destructor(void * buf) {
    printf("\tFree buffer at %p from thread %u\n", buf, (unsigned int)pthread_self());
    free(buf);
    buf = NULL;
}

static void create_key(void) {
    int res;

    printf("\tTSD Key creation from thread %u\n", (unsigned int)pthread_self());
    res = pthread_key_create(&str_key, destructor);
    if (res) {
        fprintf(stderr, "str_to_upper: TSD Key Creation ERROR!!!\n");
        exit(EXIT_FAILURE);
    }
}

char *strConstr(char *string) {
    static pthread_once_t once = PTHREAD_ONCE_INIT;

    int res = pthread_once(&once, create_key);
    if (res) {
        fprintf(stderr, "str_to_upper: Once Initialization ERROR!!!\n");
        exit(EXIT_FAILURE);
    }

    char * buf = pthread_getspecific(str_key);
    if (buf == NULL) { //First call from this thread, create buffer and store address
        buf = (char*)malloc(STR_MAX_LEN);
        if (buf == NULL) {
            fprintf(stderr, "str_to_upper: Buffer Allocation ERROR!!!\n");
            exit(EXIT_FAILURE);
        }
        printf("\tCreate buffer at %p from thread %u\n", buf, (unsigned int)pthread_self());
        res = pthread_setspecific(str_key, buf);
        if (res) {
            fprintf(stderr, "str_to_upper: setspecific ERROR!!!\n");
            exit(EXIT_FAILURE);
        }
        int index;

        for (index = 0; string[index]; index++) {
            buf[index] = string[index];
        }
        buf[index] = '\0';
    }

    return buf;
}
