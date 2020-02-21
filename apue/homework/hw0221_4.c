#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 128

void show_size(const char *path);
int main(int argc, char *argv[])
{
		
	if (argc < 2)
		return 1;

	show_size(argv[1]);

	return 0;
}

void show_size(const char *path)
{
	struct stat res;
	char buf[BUFSIZE] = {};
	DIR *dp;
	struct dirent *dir;
		
	if (stat(path, &res) == -1) {
		perror("stat()");
		return; 
	}

	if (!S_ISDIR(res.st_mode)) {
		printf("%ld %s\n", res.st_size, path);
		return;
	}
	
	dp = opendir(path);
	if (NULL == dp) {
		perror("opendir()");
		return ;
	}

	while (1) {
		dir = readdir(dp);	
		if (NULL == dir) {
			if (errno) {
				perror("readdir()");
				return ;
			}
			break;
		}
		// path /etc   passwd	
		if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) 
			continue;
		memset(buf, '\0', BUFSIZE);
		snprintf(buf, BUFSIZE, "%s/%s", path, dir->d_name);
		show_size(buf);
	}
}



