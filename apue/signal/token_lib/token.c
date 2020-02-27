#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "token.h"

static token_t *jobs[MAXTOKENS] = {};
static int inited = 0;

static void sig_handler(int s)
{
	alarm(1);
	for (int i = 0; i < MAXTOKENS; i++) {
		if (jobs[i] != NULL) {
			jobs[i]->token += jobs[i]->cps;
			if (jobs[i]->token > jobs[i]->burst)
				jobs[i]->token = jobs[i]->burst;
		}
	}
}

static void moduler_load(void)
{
	signal(SIGALRM, sig_handler);	
	alarm(1);
}

static int get_free_pos(void)
{
	for (int i = 0; i < MAXTOKENS; i++) {
		if (jobs[i] == NULL)
			return i;
	}
	return -1;
}

int token_init(int cps, int burst)
{
	token_t *t;
	int pos;

	if (inited == 0) {
		moduler_load();
		inited = 1;
	}

	t = malloc(sizeof(token_t));
	if (NULL == t) {
		fprintf(stderr, "malloc() failed\n");
		return -1;
	}
	t->token = 0;
	t->cps = cps;
	t->burst = burst;

	pos = get_free_pos();
	if (pos < 0) {
		fprintf(stderr, "have no free memery\n");
		free(t);
		return -1;
	}
	jobs[pos] = t;

	return pos;
}

int token_fetch(int td, int token)
{
	int ret;

	if (td < 0 || token <= 0)
		return -1;
	while (jobs[td]->token <= 0)
		pause();
	if (token > jobs[td]->token) {
		ret = jobs[td]->token;
		jobs[td]->token = 0;
	} else {
		ret = token;
		jobs[td]->token -= token;
	}

	return ret;
}

int token_return(int td, int token)
{
	if (td < 0 || token <= 0)	
		return -1;
	jobs[td]->token += token;
	if (jobs[td]->token > jobs[td]->burst)
		jobs[td]->token = jobs[td]->burst;
	return 0;
}

void token_destroy(int td)
{
	free(jobs[td]);
	jobs[td] = NULL;
}


