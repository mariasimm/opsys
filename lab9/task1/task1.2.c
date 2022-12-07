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
    int p_id;
    p_id = getpid(); /*process id*/
    printf("Process ID: %d\n", p_id);

    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Неможливо обробити SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    // ввічливий вихід
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Неможливо обробити SIGTERM!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGHUP, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Неможливо скинути SIGPROF!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Неможливо ігнорувати SIGUSR1!\n");
        exit(EXIT_FAILURE);
    }

    for (;;)
        pause();
    return 0;
}