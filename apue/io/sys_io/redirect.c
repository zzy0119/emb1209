#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;
	int dupfd;

	fd = open("./test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1) {
		perror("open()");
		return 1;
	}
#if 0
	// 不原子操作
	close(1);
	dupfd = dup(fd);
#endif
	// 原子操作
	dupfd = dup2(fd, 1);
	printf("dupfd:%d\n", dupfd);

	printf("hello world\n");
	fflush(NULL);
	
	close(fd);

	return 0;
}

