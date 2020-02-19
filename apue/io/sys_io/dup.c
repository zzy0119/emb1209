#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	int ret;

	fd = open("test.txt", O_RDWR);

#if 1 
	ret = fcntl(fd, F_DUPFD, 1);
	printf("ret:%d\n", ret);
#endif
	// dup2(fd, 1);

	write(1, "unix apue", 9);

	close(fd);
	
	return 0;
}

