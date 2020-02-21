#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFSIZE	1024

int main(int argc, char *argv[])
{
	time_t tm;
	struct tm *tmp;
	char buf[BUFSIZE] = {};

	// current
	time(&tm);
	tmp = localtime(&tm);
	if (NULL == tmp)
		return 1;
	tmp->tm_mday += atoi(argv[1]); // "100" 
	
	tm = mktime(tmp);
	tmp = localtime(&tm);
	if (NULL == tmp) {
		return 1;
	}
	strftime(buf, BUFSIZE, "%Y-%m-%d", tmp);
	puts(buf);

	return 0;
}

