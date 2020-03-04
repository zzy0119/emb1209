#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

#include "token.h"

#define CPS		10
#define BUFSIZE	CPS
#define BURST	CPS*10

int main(int argc, char *argv[])
{
	int fd;
	char buf[BUFSIZE] = {};
	int cnt, pos, ret;
	int td;
	int token_cnt;

	if (argc < 2)
		return 1;

	// 创建一个令牌桶－－－》控制读写流量
	td = token_init(CPS, BURST);
	if (td < 0) {
		exit(1);
	}

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
		token_cnt = token_fetch(td, CPS);
		if (token_cnt < 0) {
			fprintf(stderr, "fetch failed\n");
			goto ERROR;
		}

		cnt = read(fd, buf, token_cnt);	
		if (cnt == 0)
			break;
		if (cnt == -1) {
			// 假错
			if (errno == EINTR)
				continue;
			perror("read()");
			goto ERROR;
		}
		if (cnt < token_cnt) {
			token_return(td, token_cnt-cnt);
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

	token_destroy(td);

	close(fd);

	return 0;
ERROR:
	close(fd);
	return 1;
}
