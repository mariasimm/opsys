#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define ITERATION 10

void handler(int sig) {
    fprintf(stderr, "The pid: %d. ", (int)getpid());
    psignal(sig, "The received");
}

int main(int argc, char *argv[]) {
    static struct sigaction act;
    sigset_t set1, set2;

    sigfillset(&set1);
    sigdelset(&set1, SIGUSR1);
    sigdelset(&set1, SIGINT);

    sigfillset(&set2);
    sigdelset(&set2, SIGINT);
    sigprocmask(SIG_SETMASK, &set2, NULL);

    act.sa_handler = handler;
    sigfillset(&act.sa_mask);
    sigdelset(&act.sa_mask, SIGUSR1);
    act.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &act, NULL);

    pid_t pid = fork();

    if (pid > 0) {
        for(int i = 0; i < ITERATION; i++) {
            sigsuspend(&set1);
            kill(pid, SIGUSR1);
        }
    } else if (pid == 0) {
        for(int i = 0; i < ITERATION; i++) {
            kill(getppid(), SIGUSR1);
            sigsuspend(&set1);
        }
    } else {
        exit(EXIT_FAILURE);
    }

    return 0;
}