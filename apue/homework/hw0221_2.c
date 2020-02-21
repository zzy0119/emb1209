#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <glob.h>

#define PATTERN_SIZE	128

int regular_file_cnt(const char *path);
int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	printf("%d\n", regular_file_cnt(argv[1]));

	return 0;
}

static int except_file(const char *path)
{
	char *p = strrchr(path, '/');
	if (p == NULL)
		return 0;
	if (strcmp(p+1, ".") == 0 || strcmp(p+1, "..") == 0) {
		return 1;
	}
	return 0;
}

int regular_file_cnt(const char *path)
{
	int sum = 0;
	struct stat res;
	glob_t globres;
	char pattern[PATTERN_SIZE] = {};
	int err;

	if (stat(path, &res) == -1) {
		perror("stat()");
		return -1;
	}
	if (S_ISREG(res.st_mode)) {
		return 1;
	}
	if (!S_ISDIR(res.st_mode))
		return 0;
	
	snprintf(pattern, PATTERN_SIZE, "%s/*", path);
	if ((err = glob(pattern, 0, NULL, &globres)) != 0) {
		if (err == GLOB_NOMATCH)
			return 0;
		fprintf(stderr, "[%d]glob():%s\n", __LINE__, strerror(err));
		return -1;
	}
	memset(pattern, '\0', PATTERN_SIZE);
	snprintf(pattern, PATTERN_SIZE, "%s/.*", path);
	if ((err = glob(pattern, GLOB_APPEND, NULL, &globres)) != 0) {
		if (err == GLOB_NOMATCH)
			return 0;
		fprintf(stderr, "[%d]glob():%s\n", __LINE__, strerror(err));
		return -1;
	}

	for (int i = 0; i < globres.gl_pathc; i ++) {
		if (except_file((globres.gl_pathv)[i]))
			continue;
		sum += regular_file_cnt((globres.gl_pathv)[i]);
	}

	return sum;
}






