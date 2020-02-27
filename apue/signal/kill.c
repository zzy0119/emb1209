#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void handler(int s)
{
	;	
}

int main(void)
{
	pid_t pid;

	signal(SIGINT, handler);

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		pause();
		write(1, "world", 5);
		exit(0);
	}

	sleep(1);
	write(1, "hello", 5);
	kill(pid, SIGINT);
	wait(NULL);

	return 0;
}
