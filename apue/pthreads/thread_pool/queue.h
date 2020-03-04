#ifndef __QUEUE_H
#define __QUEUE_H

/*****************ADT*****************/
typedef struct {
	void *base;
	int front; // 队头下标
	int tail; // 队尾下标
	int size;
	int maxnmemb;
}queue_t;

// 接口
queue_t *queue_init(int size, int maxnmemb);

// 是否空
int queue_isempty(const queue_t *q);

// 是否满
int queue_isfull(const queue_t *q);

// 入队
int queue_enq(queue_t *q, const void *data);

// 出队
int queue_deq(queue_t *q, void *data);

// 销毁
void queue_destroy(queue_t *q);

#endif

