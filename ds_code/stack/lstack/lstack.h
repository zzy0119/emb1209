#ifndef __LSTACK_H
#define __LSTACK_H

#include <llist.h>
// ADT
typedef llisthead_t lstack_t;

// 初始化
lstack_t *lstack_init(int size);

// 入栈
int lstack_push(lstack_t *l, const void *data);

// 出栈
int lstack_pop(lstack_t *l, void *data);

// 栈是否为空
int lstack_isempty(const lstack_t *l);

// 销毁
void lstack_destroy(lstack_t *l);

#endif

