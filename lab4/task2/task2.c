#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#define SEC 5

int main(void) {
    pid_t pid;
    pid = fork();
    int count1 = 0, count2 = 0;
    time(NULL);
    clock_t begin = clock();
    clock_t end;
    double time;
    while (1) {
        end = clock();
        time = (double)(end - begin) / CLOCKS_PER_SEC;
        if (time >= SEC)
            break;
        if (pid == 0) {
            count1++;
        } else if (pid > 0) {
            count2++;
        } else {
            printf("Ошибка виклику fork, нащадка не створено\n");
        }
    }
    printf("\n%d | %d | time = %d sec\n", count1, count2, (int)time);
    return 0;
}
