#include <stdio.h>
#include <string.h>

#define BUFSIZE	10

int main(int argc, char *argv[])
{
	FILE *fp;
	char buf[BUFSIZE] = {};

	if (argc < 2)
		return 1;

	fp = fopen(argv[1], "r");
	if (NULL == fp) {
		fprintf(stderr, "fopen() error\n");
		return 1;
	}
	
	// 第10个字节开始读	
	fseek(fp, 10, SEEK_SET);// SEEK_CUR

	fread(buf, 1, BUFSIZE-1, fp);
	puts(buf);

	memset(buf, '\0', BUFSIZE);
	fseek(fp, -3, SEEK_CUR);
	fread(buf, 1, BUFSIZE-1, fp);
	puts(buf);

	fclose(fp);

	return 0;
}

