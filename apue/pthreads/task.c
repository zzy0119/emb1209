#if 0 

现有100~300之间的数值，用多线程筛质数

#endif
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define LEFT 	100
#define RIGHT	300

static int is_primer(int n)
{
	for (int i = 2; i <= n/2; i++) {
		if (n % i == 0)	{
			return 0;
		}
	}
	return 1;
}

static void *thr_job(void *arg)
{
	int job = (int)arg;
	
	if (is_primer(job)) {
		printf("%d is a primer\n", job);
	}

	pthread_exit((void *)0);
}

int main(void)
{
	pthread_t tids[RIGHT-LEFT+1] = {};
	int err;

	for (int i = LEFT; i <= RIGHT; i++) {
		err = pthread_create(tids+i-LEFT, NULL, thr_job, (void *)i);	
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}
	for (int i = LEFT; i <= RIGHT; i++) {
		pthread_join(tids[i-LEFT], NULL);	
	}

	exit(0);
}
