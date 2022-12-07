#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define SEED time(NULL)

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("\n1 args\n");
        return 0;
    }

    int n = atoi(argv[1]);
    printf("Arg1: %d\n", n);
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        execlp("./task7_additional.hehe", "./task7_additional.hehe", argv[1], NULL);
        perror("execv");
    }

    int status;
    pid_t wait_result;
    sleep(10);
    while ((wait_result = wait(&status)) != -1) {
        printf("\n\nProcess %lu returned result: %d\n", (unsigned long) wait_result, status / 256);
    }
    int m = (int) status / 256;
    printf("\nm(%d)/n(%d): %.3f percents\n", m, n, ((float) m/n * 100));
    return 0;
}