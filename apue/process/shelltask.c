#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <glob.h>

void parse_str(char *ptr, glob_t *res);
int main(void)
{
	char *cmdptr = NULL;
	size_t n = 0;
	pid_t pid;
	glob_t res;

	while (1) {
		printf("[emb@localhost]$ ");	
		if (getline(&cmdptr, &n, stdin) == -1) {
			fprintf(stderr, "getline() failed\n");
			exit(1);
		}
		if (!strcmp(cmdptr, "exit\n"))	
			break;
		// "ls -l     -a\n"
		parse_str(cmdptr, &res);
		pid = fork();
		if (pid < 0) {
			perror("fork()");
			exit(1);
		}
		if (pid == 0) {
			execvp((res.gl_pathv)[0], res.gl_pathv);
			perror("execvp()");
			exit(1);
		}
		wait(NULL);
	}

	exit(0);
}

void parse_str(char *ptr, glob_t *res)
{
	char *ret = NULL;
	int flag = 0;
	// strtok() strsep() ---->"ls      -l"
	while (1) {
#if 0
		ret = strtok(ptr, " \n");
		if (NULL == ret)
			break;
		if (ret[0] == '\0')
			// 分隔符连续
			continue;
#endif
		ret = strsep(&ptr, " \n");
		if (ret == NULL)
			break;
		if (*ret == '\0')
			continue;
		// "ls"
		glob(ret, GLOB_NOCHECK | GLOB_APPEND*flag, NULL, res);
		flag = 1;
		// ptr = NULL;
	}
}

