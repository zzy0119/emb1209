#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BUFSIZE	100
#define FLNAME "/tmp/out"

static int mydaemon(void)
{
	pid_t pid;
	int fd;

	umask(0);
	pid = fork();
	if (pid < 0) {
		perror("fork()");
		return -1;
	}
	if (pid > 0) {
		exit(0);
	}
	if (setsid() == -1) {
		perror("setsid()");
		return -1;
	}
	// PID == PGID == SID 
	
	fd = open("/dev/null", O_RDWR);
	if (fd < 0) {
		perror("open()");
		return -1;
	}
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd > 2)
		close(fd);

	chdir("/");
	return 0;
}	

int main(void)
{
	time_t tm;
	struct tm *tmp;
	char buf[BUFSIZE] = {};
	int fd;

	if (mydaemon() == -1) {
		exit(1);
	}
	
	fd = open(FLNAME, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0) {
		perror("open()");
		exit(1);
	}

	while (1) {
		time(&tm);	
		tmp = localtime(&tm);
		memset(buf, '\0', BUFSIZE);
		strftime(buf, BUFSIZE, "%Y/%m/%d %H:%M:%S\n", tmp);
		write(fd, buf, strlen(buf));	
		sleep(1);
	}

	exit(0);
}
