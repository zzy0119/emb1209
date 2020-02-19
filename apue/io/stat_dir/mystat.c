#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	struct stat res;	
	
	if (argc < 2)
		return 1;

	if (stat(argv[1], &res) == -1) {
		perror("stat()");
		return 1;
	}

	switch(res.st_mode & S_IFMT) {
		case S_IFREG:
			putchar('-');
			break;
		case S_IFDIR:
			putchar('d');
			break;
		default:
			puts("i don't know");
			break;
	}
	printf("\n");

	return 0;
}
