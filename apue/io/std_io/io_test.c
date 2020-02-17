#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int c;

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
		c = fgetc(fp);
		if (c == EOF) {
			if (ferror(fp)) {
				printf("ferror() error\n");
				break;
			}
			// 文件结束
			break;
		}
		printf("%c", c);
	}

	// 关闭
	if (fclose(fp) != 0) {
		printf("close failed\n");
	}

	return 0;
}
