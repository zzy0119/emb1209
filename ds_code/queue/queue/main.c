#include <stdio.h>

#include "queue.h"

int main(void)
{
	queue_t *q;
	int n;

	q = queue_init(sizeof(int), 10);

	for (int i = 1; i <= 10; i++) {
		queue_enq(q, &i);	
	}
	while (!queue_isempty(q)) {
		queue_deq(q, &n);
		printf("%d\n", n);
	}

	queue_destroy(q);

	return 0;
}

