#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

jmp_buf env;

void handler(int s)
{
	static char buf[10] = "hello";

	for (int i = 0; i < 3; i++) {
		write(1, "!", 1);
#if 0
		if (i == 1)
			longjmp(env, 1);
#endif
		sleep(1);
	}
}

void handler2(int s)
{
	write(1, "&", 1);
}

int main(void)
{
	struct sigaction act, oldact;
	// 注册行为
// 	signal(SIGINT, handler);
//	signal(SIGQUIT, handler);

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, &oldact);

	if (setjmp(env) != 0) 
		printf("jump here\n");

	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}

