#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define ITERATION 10

void handler (int signo, siginfo_t *si, void *ucontext) {
    extern const char * const sys_siglist[];
    printf("Signal %d (%s). Data from parent process: %d\n", si->si_signo, sys_siglist[si->si_signo], si->si_value.sival_int);
}

int main(int argc, char *argv[]) {
    int status;
    static struct sigaction act;
    sigval_t value;

    pid_t pid = fork();

    if (pid > 0) {
        for(int i = 0; i < ITERATION; i++) {
            sleep(1);
            value.sival_int = i + 1;
            if (sigqueue (pid, SIGUSR1, value) != 0) {
                exit(EXIT_FAILURE);
            }
        }
        sleep(2);
        kill(pid, SIGTERM);
        waitpid(pid, &status, 0);
    } else if (pid == 0) {
        sigfillset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO;
        act.sa_sigaction = handler;
        sigaction(SIGUSR1, &act, NULL);
        while (1) {
            pause();
        }
    } else {
        exit(EXIT_FAILURE);
    }

    return 0;
}