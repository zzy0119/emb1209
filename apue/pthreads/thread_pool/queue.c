#include <stdlib.h>
#include <string.h>

#include "queue.h"

#if 0
enum {LAST_DEQ, LAST_ENQ};
static int flag = LAST_DEQ;
#endif
// 接口
queue_t *queue_init(int size, int maxnmemb)
{
	queue_t *q;	

	q = malloc(sizeof(queue_t));
	if (NULL == q)
		return q;
	q->base = calloc(maxnmemb+1, size);
	if (NULL == q->base) {
		free(q);
		return NULL;
	}
	q->size = size;
	q->maxnmemb = maxnmemb;
	q->front = q->tail = 0;

	return q;
}

// 是否空
int queue_isempty(const queue_t *q)
{
	// return flag == LAST_DEQ && q->tail == q->front;	
	return q->tail == q->front;	
}

// 是否满
int queue_isfull(const queue_t *q)
{
	// return flag == LAST_ENQ && q->tail == q->front;
	return q->front == (q->tail+1) % (q->maxnmemb+1);
}

// 入队
int queue_enq(queue_t *q, const void *data)
{
	if (queue_isfull(q))
		return -1;
	memcpy((char *)q->base+q->tail*q->size, data, q->size);	
	q->tail = (q->tail+1) % (q->maxnmemb+1);

	// flag = LAST_ENQ;

	return 0;
}

// 出队
int queue_deq(queue_t *q, void *data)
{
	if (queue_isempty(q))
		return -1;
	memcpy(data, (char *)q->base+q->front*q->size, q->size);
	q->front = (q->front+1) % (q->maxnmemb+1);

	// flag = LAST_DEQ;

	return 0;
}

// 销毁
void queue_destroy(queue_t *q)
{
	free(q->base);	
	free(q);
}

