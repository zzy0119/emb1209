#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

#define THRNR	5

static int cur_id;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *thr_job(void *arg);

int main(void)
{
	pthread_t tids[THRNR] = {};
	int err;

	for (int i = 0; i < THRNR; i++) {
		err = pthread_create(tids+i, NULL, thr_job, (void *)i);	
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}

	for (int i = 0; i < THRNR; i++) {
		sleep(1);
	}
	pthread_mutex_destroy(&mut);
	pthread_cond_destroy(&cond);

	exit(0);
}

static void *thr_job(void *arg)
{
	int id = (int)arg;
	char c = 'a'+id;

	while (1) {
		pthread_mutex_lock(&mut);	
		while (cur_id != id) {
			pthread_cond_wait(&cond, &mut);
		}
		putchar(c);
		fflush(NULL);
		cur_id = (cur_id+1)%THRNR;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);
	}
}




