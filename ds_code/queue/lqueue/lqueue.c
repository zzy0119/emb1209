#include <stdio.h>
#include "lqueue.h"

lqueue_t *lqueue_init(int size)
{
	return llisthead_init(size);
}

// 空
int lqueue_isempty(const lqueue_t *q)
{
	return llist_isempty(q);
}

// 入队
int lqueue_enq(lqueue_t *q, const void *data)
{
	return llist_insert(q, data, INSERT_TAIL);
}

static int alway_cmp(const void *data, const void *key)
{
	return 0;
}

// 出队
int lqueue_deq(lqueue_t *q, void *data)
{
	return llist_fetch(q, NULL, alway_cmp, data);
}

// 销毁
void lqueue_destroy(lqueue_t *q)
{
	llist_destroy(q);
}
