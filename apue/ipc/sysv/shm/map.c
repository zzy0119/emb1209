#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
	char *ptr = NULL;
	pid_t pid;
	
	ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (MAP_FAILED == ptr) {
		perror("mmap()");
		exit(1);
	}

	pid = fork();
	if (pid < 0) {
		perror("fork()");
		goto ERROR;
	}
	if (pid == 0) {
		strcpy(ptr, "hello");		
		exit(0);
	}
	wait(NULL);
	puts(ptr);

	munmap(ptr, 1024);

	exit(0);
ERROR:
	munmap(ptr, 1024);
	exit(1);
}
