#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	int var = 100;

	pid = vfork();
	if (pid == -1) {
		perror("vfork()");
		exit(1);
	}
	if (pid == 0) {
		var ++;
		sleep(1);
		_exit(0);
	}
	printf("var:%d\n", var);

	exit(0);
}

