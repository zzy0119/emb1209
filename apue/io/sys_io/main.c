#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	char buf[10] = {};
	int cnt;

	if (argc < 2)
		return 1;

	// close(0);
	// fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open()");
		return 1;
	}

	while (1) {
		cnt = read(fd, buf, 10);	
		if (cnt == 0)
			break;
		if (cnt == -1) {
			perror("read()");
			goto ERROR;
		}
		write(1, buf, cnt);
	}

	close(fd);

	return 0;
ERROR:
	close(fd);
	return 1;
}
