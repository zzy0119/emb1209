#include <stdio.h>

#include "lstack.h"

// 初始化
lstack_t *lstack_init(int size)
{
	return llisthead_init(size);
}

// 入栈
int lstack_push(lstack_t *l, const void *data)
{
	return llist_insert(l, data, INSERT_HEAD);
}

static int always_cmp(const void *data, const void *key)
{
	return 0;
}

// 出栈
int lstack_pop(lstack_t *l, void *data)
{
	return llist_fetch(l, NULL, always_cmp, data);
}

// 栈是否为空
int lstack_isempty(const lstack_t *l)
{
	return llist_isempty(l);
}

// 销毁
void lstack_destroy(lstack_t *l)
{
	llist_destroy(l);
}
