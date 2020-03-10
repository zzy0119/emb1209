#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
	pid_t pid;
	int shmid;
	char *ptr;

	shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | IPC_EXCL | 0600);
	if (-1 == shmid) {
		perror("shmget()");
		exit(1);
	}
	pid = fork();
	if (-1 == pid) {
		perror("fork()");
		goto ERROR;
	}

	if (pid == 0) {
		ptr = shmat(shmid, NULL, 0);
		strcpy(ptr, "hello world");
		shmdt(ptr);
		exit(0);
	}
	wait(NULL);
	ptr = shmat(shmid, NULL, 0);
	puts(ptr);
	shmdt(ptr);

	exit(0);
ERROR:
	shmctl(shmid, IPC_RMID, NULL);
	exit(1);
}

