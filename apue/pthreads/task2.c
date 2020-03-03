#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define FLNAME	"/tmp/out"
#define THRNR	20
#define BUFSIZE	100

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
FILE *fp;

static void *thr_job(void *s);
int main(void)
{
	pthread_t tid[THRNR] = {};
	int err;
	
	fp = fopen(FLNAME, "w+");
	if (NULL == fp) {
		perror("fopen()");
		exit(1);
	}
	
	fprintf(fp, "%d\n", 0);

	for (int i = 0; i < THRNR; i++) {
		err = pthread_create(tid+i, NULL, thr_job, NULL);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}

	for (int i = 0; i < THRNR; i++) {
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&mut);
	fclose(fp);

	exit(0);
}

static void *thr_job(void *s)
{
	char buf[BUFSIZE] = {};

	pthread_mutex_lock(&mut);
	rewind(fp);	
	fgets(buf, BUFSIZE, fp);
	rewind(fp);
	fprintf(fp, "%d", atoi(buf)+1);
	fflush(NULL);
	pthread_mutex_unlock(&mut);

	pthread_exit((void *)0);
}






