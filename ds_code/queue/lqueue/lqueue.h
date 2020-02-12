#ifndef __LQUEUE_H
#define __LQUEUE_H

#include "/home/zhangzongyan/ds/emb1209/ds_code/llist2/llist.h"

typedef llisthead_t lqueue_t;

lqueue_t *lqueue_init(int size);

// 空
int lqueue_isempty(const lqueue_t *q);

// 入队
int lqueue_enq(lqueue_t *q, const void *data);

// 出队
int lqueue_deq(lqueue_t *q, void *data);

// 销毁
void lqueue_destroy(lqueue_t *q);

#endif

