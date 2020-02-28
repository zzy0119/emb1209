#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "anytimer.h"

void fun1(void *ptr)
{
	const char *p = ptr;
	puts(p);	
}

int main(void)
{
	//**hi*hello**workd******
	anytimer_init(3, fun1, "hello");
	anytimer_init(5, fun1, "world");
	anytimer_init(2, fun1, "hi");

	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}

