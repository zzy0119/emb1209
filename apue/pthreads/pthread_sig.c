#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>

static int flag = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static sigset_t set, oldset;

static void *thr_job(void *s)
{
	int sig;
	while (1) {
		sigwait(&set, &sig);	
		switch(sig) {
			case SIGINT:
				printf("sigint is commint\n");
				break;
			case SIGQUIT:
				pthread_mutex_lock(&mut);
				flag = 1;
				pthread_cond_signal(&cond);
				pthread_mutex_unlock(&mut);
				pthread_exit((void *)0);
			default:
				break;
		}
	}	
}

int main(void)
{
	pthread_t tid;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	pthread_sigmask(SIG_BLOCK, &set, &oldset);

	pthread_create(&tid, NULL, thr_job, NULL);	
	// if error

	pthread_mutex_lock(&mut);
	while (flag == 0)
		pthread_cond_wait(&cond, &mut);
	pthread_mutex_unlock(&mut);

	pthread_sigmask(SIG_SETMASK, &oldset, NULL);

	exit(0);
}

