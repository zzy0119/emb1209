#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

/*
 统计argv[1]文件中出现了多少次argv[2]
 ./a.out /etc/passwd "root"
 */

int main(int argc, char *argv[])
{
	int fd;
	struct stat statres;
	char *ptr;

	if (argc < 2)
		exit(1);

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open()");
		exit(1);
	}
	
	if (stat(argv[1], &statres) == -1) {
		perror("stat()");
		close(fd);
		exit(1);
	}

	ptr = mmap(NULL, statres.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == ptr) {
		perror("mmap()");
		close(fd);
		exit(1);
	}

	puts(ptr);
	munmap(ptr, statres.st_size);

	exit(0);

}
