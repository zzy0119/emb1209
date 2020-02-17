#include <stdio.h>
#include <string.h>

#define BUFSIZE	10

int main(int argc, char *argv[])
{
	FILE *fp;
	char buf[BUFSIZE] = {};
	int len = 0;

	if (argc < 2)
		return 1;

	fp = fopen(argv[1], "r");
	if (NULL == fp) {
		fprintf(stderr, "fopen() failed\n");
		return 1;
	}
	
	while (1) {
		memset(buf, '\0', BUFSIZE);
		if (fgets(buf, BUFSIZE, fp) == NULL)
			break;
		// 一行是否读完
		len += strlen(buf);
		if (strchr(buf, '\n') != NULL) {
			break;
		}
	}
	if (feof(fp)) {
		printf("没有第二行\n");
	} else {
		fseek(fp, len, SEEK_SET);
		while (1) {
			memset(buf, '\0', BUFSIZE);
			if (fgets(buf, BUFSIZE, fp) == NULL)
				break;
			fwrite(buf, 1, strlen(buf), stdout);
			if (strchr(buf, '\n') != NULL)
				break;
		}
	}

	fclose(fp);

	return 0;
}

