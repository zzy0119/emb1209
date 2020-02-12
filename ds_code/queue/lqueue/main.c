#include <stdio.h>

#include "lqueue.h"

int main(void)
{
	lqueue_t *q;	
	int deq;

	q = lqueue_init(sizeof(int));

	for (int i = 1; i <= 10; i++) {
		lqueue_enq(q, &i);	
	}

	while (!lqueue_isempty(q)) {
		lqueue_deq(q, &deq);
		printf("%d\n", deq);
	}

	lqueue_destroy(q);

	return 0;
}

