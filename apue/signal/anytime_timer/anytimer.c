#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include "anytimer.h"

static anytimer_t *timers[MAXSIZE] = {};
static int inited = 0;

static void alrm_handler(int s)
{
	for (int i = 0; i < MAXSIZE; i++) {
		if (timers[i] != NULL) {
			timers[i]->sec --;
			if (timers[i]->sec == 0) {
				(timers[i]->f)(timers[i]->arg);
				free(timers[i]);
				timers[i] = NULL;
			}
		}
	}
}

static void moduler_load(void)
{
	struct sigaction act, oldact;	
	struct itimerval itv, olditv;

	act.sa_handler = alrm_handler;
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, &oldact);

	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &itv, &olditv);

}

static int get_free_pos(void)
{
	for (int i = 0; i < MAXSIZE; i++) {
		if (timers[i] == NULL)
			return i;
	}
	return -1;
}

int anytimer_init(int sec, void (*f)(void *), void *arg)
{
	anytimer_t *tm;	
	int pos;

	if (inited == 0) {
		moduler_load();
		inited = 1;
	}

	tm = malloc(sizeof(*tm));
	// if error
	tm->sec = sec;
	tm->f = f;
	tm->arg = arg;

	pos = get_free_pos();
	timers[pos] = tm;

	return pos;
}
