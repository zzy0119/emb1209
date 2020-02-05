#include <stdlib.h>
#include <string.h>

#include "llist.h"

llisthead_t *llisthead_init(int size)
{
	llisthead_t *h;

	h = malloc(sizeof(llisthead_t));
	if (NULL == h)
		return NULL;
	h->head.prev = h->head.next = &h->head;
	h->head.data = NULL;
	h->size = size;

	return h;
}

// 插入
int llist_insert(llisthead_t *head, const void *data, int way)
{
	struct node_st *new;

	if (way != INSERT_HEAD && way != INSERT_TAIL)
		return -1;

	new = calloc(1, sizeof(*new));
	if (NULL == new)
		return -1;
	new->data = malloc(head->size);
	if (NULL == new->data) {
		free(new);
		return -1;
	}
	memcpy(new->data, data, head->size);

	if (way == INSERT_HEAD) {
		new->prev = &head->head;
		new->next = head->head.next;
	} else {
		new->prev = head->head.prev;	
		new->next = &head->head;
	}
	new->prev->next = new;
	new->next->prev = new;

	return 0;
}

// 删除
int llist_delete(llisthead_t *h, const void *key, cmp_t cmp);

// 遍历
void llist_traval(const llisthead_t *h, pri_t pri)
{
	struct node_st *cur;	

	for (cur=h->head.next; cur != &h->head; cur = cur->next) {
		pri(cur->data);
	}
}

// 销毁
void llist_destroy(llisthead_t *head);
