#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/* обробник для SIGINT */
static void signal_handler(int signo) {
    switch (signo) {
        case SIGINT:
            // Usage: kill -2 PID
            fprintf(stdout, "Сигнал переривання (SIGINT) зловлено!\n");
            break;
        case SIGTERM:
            // Usage: kill -15 PID
            fprintf(stdout, "Сигнал завершення (SIGTERM) зловлено!\n");
            break;
//            User-defined signal 1
        case SIGUSR1:
            // Usage: kill -10 PID
            fprintf(stdout, "Сигнал 1, визначений користувачем (SIGUSR1), зловлено!\n");
            exit(0);
        case SIGHUP:
            // Usage: kill -1 PID
            // do nothing
            break;
        default:
            fprintf(stderr, "Такого сигналу немає!!!");
            break;
    }
    exit(EXIT_SUCCESS);
}

int main(void) {
    printf("Process ID: %d\n", getpid());
    struct sigaction act;
    act.sa_handler = &signal_handler;
    sigfillset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    // Usage: kill -2 PID
    if (sigaction(SIGINT, &act, NULL) == -1) {
        perror("Неможливо обробити SIGINT!\n");
        exit(EXIT_FAILURE);
    }
    // Usage: kill -15 PID
    if (sigaction(SIGTERM, &act, NULL) == -1) {
        perror("Неможливо обробити SIGTERM!\n");
        exit(EXIT_FAILURE);
    }
    // Usage: kill -27 PID
    if (sigaction(SIGHUP, &act, NULL) == -1) {
        perror("Неможливо обробити SIGPROF!\n");
        exit(EXIT_FAILURE);
    }
    // Usage: kill -10 PID
    if (sigaction(SIGUSR1, &act, NULL) == -1) {
        perror("Неможливо обробити SIGUSR1!\n");
        exit(EXIT_FAILURE);
    }
    for (;;)
        pause();
    return 0;
}