#include <stdio.h>
#include <unistd.h>

#define BUFSIZE	10

int main(int argc, char *argv[])
{
	FILE *fp;
	int c;
	char buf[BUFSIZE] = {};

	if (argc < 2)
		return 1;
	// 打开  stdin stdout stderr
	fp = fopen(argv[1], "r");
	if (NULL == fp) {
		printf("fopen() error\n");
		return 1;
	}

	// 读写
	while (1) {
#if 0
		c = fgetc(fp);
		if (c == EOF) {
			if (ferror(fp)) {
				fprintf(stderr, "ferror() error\n");
				break;
			}
			// 文件结束
			break;
		}
		printf("%c", c);
#endif
#if 0
		// 行
		if (fgets(buf, BUFSIZE, fp) == NULL)
			break;
		fputs(buf, stdout);
#endif
		// 二进制io
		c = fread(buf, 1, BUFSIZE, fp);
		if (c == 0)
			break;
		fwrite(buf, 1, c, stdout);
		
// 		fflush(NULL);
		fflush(stdout);
		sleep(1);
	}

	// 关闭
	if (fclose(fp) != 0) {
		fprintf(stderr, "close failed\n");
	}

	return 0;
}
