#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    int parent_process_id = getpid();
    int opt;
    if (argc == 1) {
        printf("\nenter arguments\n");
        return 0;
    }

    printf("Current process PID/ID: %d\n", getpid());
    int num_of_childs = atoi(argv[1]);
    if (num_of_childs <= 0) {
        printf("number must > 0");
        return 1;
    }
    int arrPids[num_of_childs];
    for (int i = 0; i < num_of_childs; i++) {
        int pid = fork();
        if (pid > 0) {
            arrPids[i] = pid;
        } else if (pid == 0) {
            printf("Current process PID/ID: %d %d\n", getppid(), getpid());
            int hehe = 0;
            while (1) {
                hehe++;
            }
        }
    }
    printf("\narray:\t");
    for (int i = 0; i < num_of_childs; i++) {
        printf("%d, ", arrPids[i]);
    }
    if (parent_process_id == getpid()) {

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        system("ps");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n");
        for (int i = 0; i < num_of_childs; ++i) {
            int save = arrPids[i];
            kill(arrPids[i], SIGKILL);
            printf("Child %d has been killed!\n", save);
        }

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        system("ps");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    }
    return 0;
}

