#include <stdio.h>
#include <glob.h>

int main(int argc, char *argv[])
{
	glob_t globres;

	if (glob("/etc/*", 0, NULL, &globres) != 0) {
		return 1;
	}
	glob("/etc/.*", GLOB_APPEND, NULL,  &globres);

	for (int i = 0; i < globres.gl_pathc; i++) {
		puts((globres.gl_pathv)[i]);
	}

	globfree(&globres);

	return 0;
}
