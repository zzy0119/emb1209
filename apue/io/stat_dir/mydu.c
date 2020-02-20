#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

//实现du命令
#define BUFSIZE	128

int sizeoffile(const char *path);
int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	printf("%dK %s\n", sizeoffile(argv[1]), argv[1]);

	return 0;
}

int sizeoffile(const char *path)
{
	struct stat res;
	int sum = 0;
	DIR *dp;
	struct dirent *dr;
	char buf[BUFSIZE] = {};
	char *p;

	if (stat(path, &res) == -1) {
		perror("stat()");
		return -1;
	}
	if (!S_ISDIR(res.st_mode)) {
		return res.st_blocks / 2;
	}
 	// 累加目录本身大小	
	sum = res.st_blocks / 2;
	// 累加目录下所有文件的总大小
	dp = opendir(path);
	if (NULL == dp) {
		perror("opendir()");
		return -1;
	}
	while (1) {
		dr = readdir(dp);
		if (NULL == dr) {
			if (errno) {
				perror("readdir()");
				return -1;
			}
			break;
		}
		// "/etc"---> "/etc/passwd"
		memset(buf, '\0', BUFSIZE);
		snprintf(buf, BUFSIZE, "%s/%s", path, dr->d_name);
		// 去除"/etc/." "/etc/.." "/etc/.main.c.swp"
		p = strrchr(buf, '/');
		if (p != NULL) {
			if (strcmp(p+1, ".") == 0 || strcmp(p+1, "..") == 0) {
				continue;
			}
		}
		sum += sizeoffile(buf);
	}

	return sum;
}

