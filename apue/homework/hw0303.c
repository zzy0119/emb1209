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

static void alrm_handler(int s)
{
	pthread_mutex_destroy(&mut);
	pthread_cond_destroy(&cond);
	exit(0);
}

int main(void)
{
	pthread_t tids[THRNR] = {};
	struct sigaction act;
	int err;

	act.sa_handler = alrm_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM, &act, NULL);

	alarm(5);
	
	for (int i = 0; i < THRNR; i++) {
		err = pthread_create(tids+i, NULL, thr_job, (void *)i);	
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}
	for (int i = 0; ; i = (i+1) % THRNR) {
		pthread_mutex_lock(&mut);	
		while (cur_id != -1) {
			pthread_cond_wait(&cond, &mut);
		}
		cur_id = i;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);
	}

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
		cur_id = -1;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);
	}
}




