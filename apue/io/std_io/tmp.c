#include <stdio.h>

int main(void)
{
#if 0
	char *p = tmpnam(NULL);
	char *q = tmpnam(NULL);
	puts(p);
	puts(q);
#endif

	FILE *fp;
	char buf[] = "hello world";
	char res[100] = {};

	fp = tmpfile();
	if (NULL == fp) {
		perror("tmpfile()");
		return 1;
	}

	fwrite(buf, 1, 11, fp);
	// fseek(fp, 0, SEEK_SET);
	rewind(fp);
	fgets(res, 100, fp);
	puts(res);

	fclose(fp);

	return 0;
}
