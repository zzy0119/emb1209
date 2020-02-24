#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int n = 100;

	pid = getpid();
	printf("the process id is %d, the parents is %d\n", \
			pid, getppid());
	
	printf("hello");

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		exit(1);
	}
	// 父子进程没有严格的先后顺序
	// 有相同的两份代码同时运行
	if (pid == 0) {
		// child
		printf("[%d] i am the new child process\n", getpid());
		printf("n:%d\n", n);
		n ++;
	} else {
		wait(NULL);
		// parent 父进程（调用进程） pid就是子进程id
		printf("[%d] i am parent, my child is %d\n", \
				getpid(), pid);
		printf("n:%d\n", n);
	}

	return 0;
}

