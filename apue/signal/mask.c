#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void sig_handler(int s)
{
	write(1, "!", 1);
}

int main(void)
{
	sigset_t set, old;

	signal(SIGINT, sig_handler);
	
	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	for (int i = 0; i < 5; i++) {
		sigprocmask(SIG_BLOCK, &set, &old);
		for (int j = 0; j < 5; j++)	{
			write(1, "*", 1);
			sleep(1);
		}
		write(1, "\n", 1);	
		sigprocmask(SIG_SETMASK, &old, NULL);
	}

	exit(0);
}

