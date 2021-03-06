#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <syslog.h>
#include <sys/file.h>

#define BUFSIZE		100
#define FLNAME 		"/tmp/out"
#define LOCKFLNAME	"/var/run/daemon.pid"

static int singal_running(void);
static int mydaemon(void)
{
	pid_t pid;
	int fd;

	umask(0);
	pid = fork();
	if (pid < 0) {
// 		perror("fork()");
		syslog(LOG_ERR, "fork():%s", strerror(errno));
		return -1;
	}
	if (pid > 0) {
		exit(0);
	}
	if (setsid() == -1) {
		// perror("setsid()");
		syslog(LOG_ERR, "setsid():%s", strerror(errno));
		return -1;
	}
	// PID == PGID == SID 
	
	fd = open("/dev/null", O_RDWR);
	if (fd < 0) {
		syslog(LOG_ERR, "open():%s", strerror(errno));
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
	
	// 创建链接
	openlog("mydaemon", LOG_PID | LOG_PERROR, LOG_DAEMON);

	// 单实例
	if (singal_running() == -1) {
		syslog(LOG_ERR, "signal_running() failed");
		exit(1);
	}

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
		syslog(LOG_INFO, "%s write succesfully", buf);
		sleep(1);
	}

	closelog();

	exit(0);
}

// 单实例

static int singal_running(void)
{
	int fd;
	char buf[BUFSIZE] = {};

	fd = open(LOCKFLNAME, O_RDWR | O_CREAT, 0666);
	if (fd < 0) {
		syslog(LOG_ERR, "open():%s", strerror(errno));
		exit(1);
	}

	if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
		syslog(LOG_ERR, "flock():%s", strerror(errno));
		close(fd);
		return -1;
	}

	ftruncate(fd, 0);
	snprintf(buf, BUFSIZE, "%d", getpid());
	write(fd, buf, strlen(buf));

	return 0;
}



