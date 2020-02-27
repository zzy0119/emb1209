#ifndef __TOKEN_H
#define __TOKEN_H

#define MAXTOKENS	1024

typedef struct {
	int token;
	int cps;
	int burst;
}token_t;

/*
return:桶描述符
 */
int token_init(int cps, int burst);

int token_fetch(int td, int token);

int token_return(int td, int token);

void token_destroy(int td);

#endif

