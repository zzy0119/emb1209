#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>

#if 0
流量控制:
	漏桶
#endif

#define CPS		10
#define BUFSIZE	CPS

static int token;

static void handler(int s)
{
	//alarm(1);
	token = 1;
}

int main(int argc, char *argv[])
{
	int fd;
	char buf[BUFSIZE] = {};
	int cnt, pos, ret;
	struct itimerval itm;

	if (argc < 2)
		return 1;
	signal(SIGALRM, handler);
//	alarm(1);
	itm.it_interval.tv_sec = 0;
	itm.it_interval.tv_usec = 500000;
	itm.it_value.tv_sec = 3;
	itm.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &itm, NULL);

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
		while (token == 0)
			pause();
		token = 0;

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
