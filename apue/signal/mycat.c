#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	int fd;
	char buf[10] = {};
	int cnt, pos, ret;

	if (argc < 2)
		return 1;

	// close(0);
	// fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
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
		cnt = read(fd, buf, 10);	
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
