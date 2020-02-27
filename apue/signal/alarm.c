#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void handler(int s)
{
	alarm(3);
	write(1, "!", 1);
}

int main(void)
{
	signal(SIGALRM, handler);
	alarm(3);

	while (1) {
		write(1, "*", 1);
		sleep(1);
	} 

	exit(0);
}

