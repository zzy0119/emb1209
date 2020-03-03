#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

#define THRNR	5

static pthread_mutex_t mut[THRNR];

static void *thr_job(void *arg);

int main(void)
{
	pthread_t tids[THRNR] = {};
	int err;

	for (int i = 0; i < THRNR; i++ ) {
		pthread_mutex_init(mut+i, NULL);
		pthread_mutex_lock(mut+i);
		err = pthread_create(tids+i, NULL, thr_job, (void *)i);	
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}
	
	pthread_mutex_unlock(mut+0);

	for (int i = 0; i < THRNR; i++) {
		sleep(1);
	}
	for (int i = 0; i < THRNR; i++)
		pthread_mutex_destroy(mut+i);

	exit(0);
}

static void *thr_job(void *arg)
{
	int id = (int)arg;
	char c = 'a'+id;

	while (1) {
		pthread_mutex_lock(mut+id);	
		putchar(c);
		fflush(NULL);
		pthread_mutex_unlock(mut+(id+1)%THRNR);
	}
}




