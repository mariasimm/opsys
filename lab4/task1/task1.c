#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <sys/types.h>

extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char *argv[]) {

    int opt;
    if (argc == 1) {
        help();
        return 0;
    }

    while ((opt = getopt(argc, argv, "abcdefg")) != -1) {
        switch (opt) {
            case 'a':
                printf("Current process ID: %d\n", getpid());
                break;
            case 'b':
                printf("Current process PID: %d\n", getppid());
                break;
            case 'c':
                printf("ID of group, which executes process: %d\n", getpgrp());
                break;
            case 'd':
                printf("Current process UID: %d\n", (int) getuid());
                break;
            case 'e':
                printf("Current process eUID: %d\n", (int) geteuid());
                break;
            case 'f':
                printf("Current process GID: %d\n", (int) getgid());
                break;
            case 'g':
                printf("eGID: %d\n", getegid());
                break;
        }
    }
}

void help() {
    printf("NAME\n"
           "       main - a program that outputs in a standard flow of process output\n\n"
           "SYNOPSIS\n"
           "       ./hehe [OPTION]...\n\n"
           "DESCRIPTION\n"
           "       -a prints current process ID\n\n"
           "       -b prints current process PID\n\n"
           "       -c prints ID of group, which executes process\n\n"
           "       -d prints current process UID\n\n"
           "       -e prints current process eUID: %d\n\n"
           "       -f prints current process GID\n\n"
           "       -g prints eGID\n\n"
           "AUTHOR\n"
           "       Written by a very good person from CS.\n\n"
           "COPYRIGHT\n"
           "       Copyright  ©  2018  Free Foundation, Inc.  License\n"
           "       GPLv3+: GNU  GPL  version  3  or  later  <https://gnu.org/li‐\n"
           "       censes/gpl.html>.\n"
           "       This  is  free  software:  you  are free to change and redis‐\n"
           "       tribute it.  There is NO WARRANTY, to the extent permitted by\n"
           "       law.\n\n"
    );

}