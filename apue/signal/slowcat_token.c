#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#if 0
流量控制:
	令牌桶模型
		令牌 
		速率
		上限
#endif

#define CPS		10
#define BUFSIZE	CPS
#define BURST	CPS*10

static int token;

static void handler(int s)
{
	alarm(1);
	token += CPS;
	if (token >= BURST) {
		token = BURST;
	}
}

int main(int argc, char *argv[])
{
	int fd;
	char buf[BUFSIZE] = {};
	int cnt, pos, ret;

	if (argc < 2)
		return 1;
	signal(SIGALRM, handler);
	alarm(1);

	do {
		fd = open(argv[1], O_RDONLY);
		if (fd == -1) {
			if (errno == EINTR)
				continue;
			perror("open()");
			return 1;
		}
	} while(fd < 0);

	while (1) {
		while (token <= 0)
			pause();
		token -= CPS;

		cnt = read(fd, buf, CPS);	
		if (cnt == 0)
			break;
		if (cnt == -1) {
			// 假错
			if (errno == EINTR)
				continue;
			perror("read()");
			goto ERROR;
		}
		pos = 0;
		while (1) {
			ret = write(1, buf+pos, cnt);
			if (ret == -1) {
				if (errno == EINTR)
					continue;
				perror("write()");
				goto ERROR;
			}
			if (ret < cnt) {
				pos	+= ret;
				cnt -= ret;
			} else {
				break;
			}
		}
	}

	close(fd);

	return 0;
ERROR:
	close(fd);
	return 1;
}
