#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void reg_exit1(void)
{
	printf("%s is called\n", __FUNCTION__);
}

static void reg_exit2(void)
{
	printf("%s is called\n", __FUNCTION__);
}

static void reg_exit3(void)
{
	printf("%s is called\n", __FUNCTION__);
}

static int test(void)
{
	printf("%s is running....", __FUNCTION__);
	write(1, "world", 5);
	// return 0;
	exit(0);
	// _exit(0);
}

int main(void)
{

	atexit(reg_exit1);
	atexit(reg_exit2);
	atexit(reg_exit3);
	
	test();
	
	printf("hello\n");

	// return 0;
	exit(EXIT_SUCCESS);
}

