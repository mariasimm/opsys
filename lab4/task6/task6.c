#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main (void) {
    int status;
    int pid;

    if ((pid = fork()) == 0) {
        execlp("ls", "ls", NULL);
        fprintf (stderr, "Exec error\n");
        printf("Process ID: %d", pid);
        exit(0);
    }
    hr();
    system("ps");
    hr();
    sleep(40);

    wait(&status);
    if (WIFEXITED (status)) {
        printf ("Code=%d\n", WEXITSTATUS(status));
    }
    hr();
    system("ps");
    hr();
    return 0;
}

void hr() {
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}