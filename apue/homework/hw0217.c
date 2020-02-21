#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSIZE	100

int insertStrToFile(const char *str, FILE *fp, int line);
int main(int argc, char *argv[])
{
	FILE *fp;
	if (argc < 3)
		return 1;
	
	fp = fopen(argv[1], "r+");
	// if error

	insertStrToFile(argv[2], fp, 3);

	return 0;
}
static int fileToFile(FILE *src, FILE *dest)
{
	char *lineptr;
	size_t n;
	ssize_t ret;

	while (1) {
		lineptr = NULL;
		n = 0;
		ret = getline(&lineptr, &n, src);
		if (ret == -1) {
			if (!errno) {
				break;
			}
			perror("getline()");
			return -1;
		}
		fputs(lineptr, dest);	
		free(lineptr);
	}
	return 0;
}

int insertStrToFile(const char *str, FILE *fp, int line)
{
	size_t n = 0;	
	char *lineptr = NULL;
	ssize_t ret;
	int linecnt = 1;
	int pos;
	FILE *tmp;

	while (1) {
		if (linecnt == line)
			break;
		ret = getline(&lineptr, &n, fp);
		if (ret == -1) {
			if (!errno) {
				// 文件结束, 没有第Line行
				return -1;
			}
			perror("getline()");
			return -1;
		}
		linecnt++;
	}
	free(lineptr);
	pos = ftell(fp);

	tmp = tmpfile();
	if (NULL == tmp) {
		perror("tmpfile()");
		return -1;
	}
	
	fileToFile(fp, tmp);

	fseek(fp, pos, SEEK_SET);
	fputs(str, fp);	
	// 存放到临时文件的数据写回来
	rewind(tmp);
	fileToFile(tmp, fp);
	
	fclose(tmp);
	return 0;
}

