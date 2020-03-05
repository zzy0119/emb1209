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
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	// pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	err = pthread_create(&tid, NULL, thr_job, NULL);
	// err = pthread_create(&tid, &attr, thr_job, NULL);
	if (err) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));
		exit(1);
	}

	err = pthread_join(tid, NULL);
	if (err) {
		fprintf(stderr, "pthread_join():%s\n", strerror(err));
	}

	while (1) {
		write(1, "*", 1);
		sleep(1);
	}
	printf("main thread end\n");

	exit(0);
}

