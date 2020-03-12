#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "proto.h"

// 动态进程池
#define MAX_PROC_NR	30
#define MIN_FREE_NR	4
#define MAX_FREE_NR	8

#define NOTIFY_SIG	SIGUSR1

enum {
	STATE_INVAL,// 无效
	STATE_FREE,
	STATE_BUSY
};

typedef struct proc_entry_st {
	pid_t pid;
	int state;
}pool_t;

static void user1_handler(int s)
{
	;
}

int main(void)
{
	pool_t *pool;	
	int sd;
	struct sigaction act, oldact;

	// 池创建
	pool = mmap(NULL, sizeof(pool_t)*MAX_PROC_NR, PROT_READ | PROT_WRITE, \
			MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (MAP_FAILED == pool) {
		perror("map()");
		exit(1);
	}

	// 构建套接字
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto SOCKET_ERROR;
	}
	if (listen(sd, MAX_PROC_NR) == -1) {
		perror("listen()");
		goto LISTEN_ERROR;
	}

	// 注册信号行为
	act.sa_handler = user1_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(NOTIFY_SIG, &act, &oldact);
			
	// 子进程当终止是不变成僵尸进程
	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, NULL);

	
	

	exit(0);
LISTEN_ERROR:
	close(sd);
SOCKET_ERROR:
	munmap(pool, sizeof(pool_t)*MAX_PROC_NR);
	exit(1);
}

