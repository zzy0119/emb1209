#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;

	pid = fork();
	// if error
	if (pid == 0) {
		// 设置进程组
		setpgid(0, getpid());
		printf("child: pid:%d, ppid:%d, pgid:%d, sid:%d\n", getpid(), \
				getppid(), getpgrp(), getsid(getpid()));	
		exit(0);
	}
	wait(NULL);
	printf("parent: pid:%d, ppid:%d, pgid:%d, sid:%d\n", getpid(), \
			getppid(), getpgrp(), getsid(getpid()));	

	exit(0);
}
