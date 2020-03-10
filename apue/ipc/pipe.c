#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE	100

int main(void)
{
	int pfd[2] = {};
	pid_t pid;
	char buf[BUFSIZE] = {};

	if (pipe(pfd) == -1) {
		perror("pipe()");
		exit(1);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		close(pfd[1]);	
		read(pfd[0], buf, BUFSIZE);
		puts(buf);
		close(pfd[0]);
		exit(0);
	}
	sleep(1);
	close(pfd[0]);
	write(pfd[1], "hello", 5);
	wait(NULL);
	close(pfd[1]);

	exit(0);
}

