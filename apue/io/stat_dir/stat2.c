#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat res;

	if (argc < 2)
		return 1;

	if (stat(argv[1], &res) == -1) {
		perror("stat()");
		return 1;
	}
	printf("%ld\n", res.st_blocks / 2);

	printf("%ld\n", res.st_ino);

	return 0;
}

