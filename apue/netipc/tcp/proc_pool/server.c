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

static void P(int semid);
static void V(int semid);

static void user1_handler(int s)
{
	;
}

int main(void)
{
	pool_t *pool;	
	int sd;
	struct sigaction act, oldact;
	sigset_t set, oldset;
	int freecnt, busycnt;
	int semid;

	// 池创建
	pool = mmap(NULL, sizeof(pool_t)*MAX_PROC_NR, PROT_READ | PROT_WRITE, \
			MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (MAP_FAILED == pool) {
		perror("map()");
		exit(1);
	}

	// 初始化池
	for (int i = 0; i < MAX_PROC_NR; i++) {
		pool[i].pid = -1;
		pool[i].state = STATE_INVAL;
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

	// 初始化信号量
	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0600);
	if (semid < 0) {
		perror("semget()");
		goto LISTEN_ERROR;
	}
	semctl(semid, 0, SETVAL, 1);

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

	// 最少有MIN_FREE_NR个空闲线程
	for (int i = 0; i < MIN_FREE_NR; i++) {
		pool_add_proc(pool, semid, sd);	
	}

	// 信号集
	sigemptyset(&set);
	sigaddset(&set, NOTIFY_SIG);
	sigprocmask(SIG_BLOCK, &set,　&oldset);

	// 管理进程池
	while (1) {
		sigsuspend(&oldset);
		freecnt = 0;
		busycnt = 0;		
		P(semid);
		for (int i = 0; i < MAX_PROC_NR; i++) {
			if (pool[i].pid < 0 && pool[i].state == STATE_INVAL)
				continue;
			if (kill(pool[i].pid, 0)) {
				// 进程不存在
				pool[i].pid = -1;
				pool[i].state = STATE_INVAL;
				continue;
			}
			if (pool[i].state == STATE_FREE)
				freecnt ++;
			else if (pool[i].state == STATE_BUSY)
				busycnt ++;
		}

		if (freecnt < MIN_FREE_NR) {
			// 添加进程
			for (int i = 0; i < MIN_FREE_NR-freecnt; i++) {
				pool_add_proc(pool, semid, sd);	
			}
		}
		else if (freecnt > MAX_FREE_NR) {
			// 多了　减少进程
			for (int i = 0; i < freecnt-MAX_FREE_NR; i++) {
				pool_del_proc(pool, semid);	
			}
		}
		V(semid);
	}

	exit(0);
LISTEN_ERROR:
	close(sd);
SOCKET_ERROR:
	munmap(pool, sizeof(pool_t)*MAX_PROC_NR);
	exit(1);
}

// P V 操作
// 取信号
static void P(int semid)
{
	struct sembuf sbf;

	sbf.sem_num = 0;
	sbf.sem_op = -1;
	sbf.sem_flg = 0;

	if (semop(semid, &sbf, 1) == -1) {
		perror("semop()");
		exit(1);
	}
}

// 还信号
static void V(int semid)
{
	struct sembuf sbf;

	sbf.sem_num = 0;
	sbf.sem_op = 1;
	sbf.sem_flg = 0;

	if (semop(semid, &sbf, 1) == -1) {
		perror("semop()");
		exit(1);
	}
}

// 添加
static int pool_add_proc(pool_t *pool, int semid, int sd)
{
	pid_t pid;	
	int i;

	P(semid);	
	for (i = 0; i < MAX_PROC_NR; i++) {
		if (pool[i].pid == -1 && pool[i].state == STATE_INVAL)
			break;
	}
	if (i == MAX_PROC_NR) {
		V(semid);
		return -1;
	}
 
	pid = fork();
	if (pid < 0) {
		perror("fork()");
		return -1;
	}
	if (pid == 0) {
		// 子进程	
		child_job(pool, semid, sd);
		exit(0);
	}
	pool[i].pid = pid;
	pool[i].state = STATE_FREE;
	V(semid);

	return 0;
}

static int pool_del_proc(pool_t *pool, int semid)
{
	int i;

	P(semid);
	for (i = 0; i < MAX_PROC_NR; i++) {
		if (pool[i].state == STATE_FREE && pool[i].pid > 0)	{
			kill(pool[i], SIGTERM);	
			pool[i].pid = -1;
			pool[i].state = STATE_INVAL;
			break;
		}
	}
	V(semid);
	if (i == MAX_PROC_NR)
		return -1;

	return 0;
}







