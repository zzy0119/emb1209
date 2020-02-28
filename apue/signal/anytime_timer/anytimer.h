#ifndef __ANYTIMER_H
#define __ANYTIMER_H

#define MAXSIZE	1024

typedef struct {
	int sec;
	void (*f)(void *p);
	void *arg;
}anytimer_t;

int anytimer_init(int sec, void (*f)(void *), void *arg);

#endif

