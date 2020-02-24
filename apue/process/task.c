#if 0
创建４个子进程，调用进程要将筛选100－300的质数求出来的任务
分配给４个子进程，分别打印出所筛选的质数，并附上其pid
#endif
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define START 	100
#define END		300

#define PRONR	4

static int isprimer(int n);
int main(void)
{
	int arr[END-START+1] = {};
	pid_t pid;

	for (int i = START; i <= END; i++) {
		arr[i-START] = i;	
	}

	for (int i = 0; i < PRONR; i++) {
		pid = fork();
		if (pid == -1) {
			perror("fork()");
			exit(1);
		}
		if (pid == 0) {
			for (int j = i; j < END-START+1; j += PRONR) {
				if (isprimer(arr[j])) {
					printf("[%d]%d is a primer\n", getpid(), arr[j]);
				}
			}
			exit(0);
		}
	}
	
	for (int i = 0; i < PRONR; i++) {
		wait(NULL);	
	}

	return 0;
}

static int isprimer(int n)
{
	for (int i = 2; i <= n / 2; i++) {
		if (n % i == 0)
			return 0;
	}
	return 1;
}




