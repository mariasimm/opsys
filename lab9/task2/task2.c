#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <wait.h>

struct toProcess {
    int seconds;
    char* msg;
};

struct toProcess data;

sig_atomic_t alarm_flag = 0;

void setflag(int sig) {
    alarm_flag = 1;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        data.seconds = 2;
        data.msg = "standard message";
    } else if (argc != 3) {
        printf("Вам необхідно ввести 2 аргументи!");
    } else {
        data.seconds = atoi(argv[1]);
        data.msg = argv[2];
    }

    pid_t pid = fork();

    if (pid > 0) {
        int status;
        pid = wait(&status);
        printf("\n[Parent process] Child with PID %d finishes ", (int)pid);
        if (WIFEXITED(status)) {
            printf("normally with code %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("due to signal\n");
        }
    } else if (pid == 0) {
        static struct sigaction act;

        act.sa_handler = setflag;
        sigaction(SIGALRM, &act, NULL);
        alarm(data.seconds);
        pause();
        if (alarm_flag == 1) {
            printf("\n[Child process] ");
            printf("Alarm\n");
            printf("%s\n", data.msg);
        }
    } else {
        exit(EXIT_FAILURE);
    }

    return 0;
}