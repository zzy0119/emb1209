#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

/*
 模拟ｓｈｅｌｌ的工作方式

 while (1) {
 	printf("[xxx@localhost]$");
	// read stdin
 }
 */

int main(void)
{
	pid_t pid;	
	char *list[] = {"ls", "-l", NULL};

	printf("good morning\n");

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		// ls替换子进程		
		// execl("/bin/ls", "ls", "-l", NULL);
#if 0
		puts(getenv("PATH"));
		setenv("PATH", ".", 1);
#endif
		// execlp("jmp", "jmp", NULL);
		execv("/bin/ls", list);
		perror("execl()");
		exit(1);
	}
	wait(NULL);
	printf("bye bye\n");

	exit(0);
}
