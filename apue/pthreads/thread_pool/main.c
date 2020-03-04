#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pool.h"

#define LEFT	100
#define RIGHT	300

static void *thr_fun(void *arg);

int main(void)
{
	threadpool_t *pool;

	pool = threadpool_init(50, 5, 20);
	// if error

	for (int i = LEFT; i <= RIGHT; i++) {
		threadpool_add_task(pool, thr_fun, (void *)i);
	}
	
	while (1) {
		// 等待客户端请求	
		;
	}

	threadpool_destroy(pool);

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

// 任务
static void *thr_fun(void *arg)
{
	int n = (int)arg;
	
//	printf("%d will be caculate\n", n);

	if (is_primer(n)) {
		printf("%d is a primer\n", n);
		// sleep(1);
	}
	return NULL;
}



