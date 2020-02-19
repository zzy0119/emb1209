#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[])
{
	struct stat res;	
	
	if (argc < 2)
		return 1;

	if (stat(argv[1], &res) == -1) {
		perror("stat()");
		return 1;
	}

	if (S_ISREG(res.st_mode))
		putchar('-');
	else if (S_ISDIR(res.st_mode))
		putchar('d');

#if 0
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
#endif

	// 文件权限 st_mode  arr[] = {-------}
	if (res.st_mode & S_IRUSR)
		putchar('r');
	else
		putchar('-');
	if (res.st_mode & S_IWUSR)
		putchar('w');
	else
		putchar('-');
	if (res.st_mode &S_IXUSR) {
		if (res.st_mode & S_ISUID)
			putchar('s');
		else
			putchar('x');
	}else
		putchar('-');

	// 硬链接个数
	printf(" %ld ", res.st_nlink);

	// 拥有者 所属组
	struct passwd *pwd = getpwuid(res.st_uid);
	if (NULL == pwd)
		return 1;
	printf("%s ", pwd->pw_name);
	struct group *grp = getgrgid(res.st_gid); 
	if (NULL == grp)
		return 1;
	printf("%s ", grp->gr_name);

	printf("\n");
	return 0;
}
