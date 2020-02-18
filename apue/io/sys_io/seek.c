#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE	100

int main(int argc, char *argv[])
{
	int fd;
	int pos;
	char buf[BUFSIZE] = {};
	int cnt;

	fd = open(argv[1], O_RDWR);	
	if (fd == -1) {
		perror("open()");
		return 1;
	}

	pos = lseek(fd, 5, SEEK_CUR);

	cnt = read(fd, buf, BUFSIZE);

	write(1, buf, cnt);

	lseek(fd, 0, SEEK_END);

	lseek(fd, 1024*1024, SEEK_CUR);
	write(fd, "hello", 5);

	close(fd);

	return 0;
}
