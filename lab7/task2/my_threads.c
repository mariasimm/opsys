#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "my_threads.h"
#include "integr.h"

typedef struct {
	double * res;
	pthread_mutex_t *m;
	TARG arg;
} THREAD_ARG;

static void * integr_thread(void * arg) {
	THREAD_ARG data = *(THREAD_ARG*) arg;
	double res;
	res = NIntegrate(data.arg.f, data.arg.a, data.arg.b, data.arg.eps);
	pthread_mutex_lock(data.m);
	*data.res += res;
	pthread_mutex_unlock(data.m);
	return NULL;
}

double Thread_NIntegrate(const TARG * arg) {
	int i;
	double h, result;
	pthread_mutex_t total_res_mutex;
	pthread_t *thread;
	THREAD_ARG *arr;
	
	result = 0;
	h = (arg->b - arg->a) / arg->n;
	if (pthread_mutex_init(&total_res_mutex, NULL)) {
		fprintf(stderr, "ERROR! %s\n", "Cannot initialize mutex!");
		exit(EXIT_FAILURE);
	}
	thread = (pthread_t*)malloc(arg->n * sizeof(pthread_t));
	arr = (THREAD_ARG*)malloc(arg->n * sizeof(THREAD_ARG));
	if ((thread == NULL) || (arr == NULL)) {
		fprintf(stderr, "Allocation Memory Error\n");
		exit(EXIT_FAILURE);
	}
	
	for (i = 0; i < arg->n; i++) {
		arr[i].res = &result;
		arr[i].m = &total_res_mutex;
		arr[i].arg.n = i;
		arr[i].arg.a = arg->a + i*h;
		arr[i].arg.b = arr[i].arg.a + h;
		arr[i].arg.eps = arg->eps;
		arr[i].arg.f = arg->f;
		if (pthread_create(&thread[i], NULL, &integr_thread, &arr[i]) != 0) {
			fprintf(stderr, "Score Thread %d Creation Error\n", i);
			exit(EXIT_FAILURE);
		}
	}
	
	for (i = 0; i < arg->n; i++) {
		if (pthread_join(thread[i], NULL) != 0) {
			fprintf(stderr, "Score Thread %d Waiting Error\n", i);
			exit(EXIT_FAILURE);
		}
	}
	
	pthread_mutex_destroy(&total_res_mutex);
	free(thread); free(arr);
	return result;
}