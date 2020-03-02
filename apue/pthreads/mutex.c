#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sched.h>

#define LEFT	100
#define RIGHT	300

#define THR_NR	4

/*
 job == 0	任务还未发放
 job == -1　所有任务发放完成
 job > 0	所发放的任务
 */
static int job;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *thr_fun(void *arg);
int main(void)
{
	pthread_t tids[THR_NR] = {};
	int err;

	for (int i = 0; i < THR_NR; i++) {
		err = pthread_create(tids+i, NULL, thr_fun, NULL);	
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}
	// 任务的发放
	for (int j = LEFT; j <= RIGHT; j++) {
		pthread_mutex_lock(&mutex);
		while (job != 0) {
			pthread_mutex_unlock(&mutex);
			sched_yield(); // 优先调度其他线程
			pthread_mutex_lock(&mutex);
		}
		job = j;		
		pthread_mutex_unlock(&mutex);
	}

	// 告诉其他线程，任务已发放完成
	pthread_mutex_lock(&mutex);
	while (job > 0) {
		pthread_mutex_unlock(&mutex);
		sched_yield();
		pthread_mutex_lock(&mutex);
	}
	job = -1;
	pthread_mutex_unlock(&mutex);

	for (int i = 0; i < THR_NR; i++)
		pthread_join(tids[i], NULL);

	pthread_mutex_destroy(&mutex);

	exit(0);
}

static int is_primer(int n)
{
	for (int i = 2; i <= n/2; i++) {
		if (n % i == 0)	{
			return 0;
		}
	}
	return 1;
}
// 任务线程
static void *thr_fun(void *arg)
{
	int j;
	while (1) {
		pthread_mutex_lock(&mutex);
		if (job == -1) {
			pthread_mutex_unlock(&mutex);
			pthread_exit((void *)0);
		}
		if (job == 0) {
			pthread_mutex_unlock(&mutex);
			sched_yield();
			continue;
		}
		j = job;
		job = 0; // 任务已取走
		pthread_mutex_unlock(&mutex);
		if (is_primer(j)) {
			printf("%d is a primer\n", j);
		}
	}
}

