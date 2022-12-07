#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define SEED time(NULL)

int main(int argc, char *argv[]) {
    int i, count, n;
    double x,y,s,pi;

    srand( SEED );
    n = atoi(argv[1]);

    count = 0;

    for(i = 0; i < n; ++i) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        s = x * x + y * y;
        if( s <= 1 ) count++;
    }

    pi = (double) count / n * 4;

    printf("Approximate PI = %g", pi);
    return count;
}