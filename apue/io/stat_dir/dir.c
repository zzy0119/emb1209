#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	struct stat statres;
	DIR *dp = NULL;
	struct dirent *dr;

	if (argc < 2)
		return 1;

	if (stat(argv[1], &statres) == -1) {
		perror("stat()");
		return 1;
	}
	if (!S_ISDIR(statres.st_mode)) {
		fprintf(stderr, "%s is not a dircectory\n", argv[1]);
		return 1;
	}

	dp = opendir(argv[1]);
	if (NULL == dp) {
		perror("opendir()");
		return 1;
	}

	while (1) {
		dr = readdir(dp);
		if (dr == NULL) {
			if (errno) {
				perror("readdir");
				return 1;
			}
			break;
		}
		printf("%s\n", dr->d_name);
	}

	closedir(dp);

	return 0;
}

