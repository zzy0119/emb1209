#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static void *thr_job(void *arg)
{
	write(1, "new thread", 10);
	// return NULL;
	pthread_exit((void *)0);
}

int main(void)
{
	pthread_t tid;	
	int err;

	err = pthread_create(&tid, NULL, thr_job, NULL);
	if (err) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));
		exit(1);
	}

	pthread_join(tid, NULL);

	printf("main thread end\n");

	exit(0);
}

