#include <stdio.h>

#define BUFSIZE	100

int reverseFile(const char *path);
int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	reverseFile(argv[1]);

	return 0;
}

int reverseFile(const char *path)
{
	FILE *fp, *tmp;
	int c;
	int length;
	char buf[BUFSIZE] = {};
	int cnt;

	fp = fopen(path, "r+");	
	if (NULL == fp) {
		perror("fopen()");
		return -1;
	}

	tmp = tmpfile();
	if (NULL == tmp) {
		perror("tmpfile()");
		fclose(fp);
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	length = ftell(fp);

	while (length > 0) {
		fseek(fp, -1, SEEK_CUR);	
		c = fgetc(fp);
		if (c == 0) {
			fprintf(stderr, "fgets() failed\n");
			goto ERROR;
		}
		fseek(fp, -1, SEEK_CUR);	
		fputc(c, tmp);
		length --;
	}

	rewind(tmp);
	while (1) {
		cnt = fread(buf, 1, BUFSIZE, tmp);	
		if (cnt == 0) {
			if (ferror(fp)) {
				fprintf(stderr, "fread() failed\n");
				goto ERROR;
			}
			break;	
		}
		fwrite(buf, 1, cnt, fp);
	}

	fclose(fp);
	fclose(tmp);
	return 0;
ERROR:
	fclose(fp);
	fclose(tmp);

	return -1;
}

