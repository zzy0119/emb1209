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

static struct node_st *find_node(const llisthead_t *h, const void *key, cmp_t cmp)
{
	struct node_st *cur;

	for (cur = h->head.next; cur != &h->head; cur = cur->next) {
		if (cmp(cur->data, key) == 0) {
			return cur;
		}
	}
	return NULL;
}

// 删除
int llist_delete(llisthead_t *h, const void *key, cmp_t cmp)
{
	struct node_st *del;

	del = find_node(h, key, cmp);
	if (del == NULL)
		return -1;
	del->prev->next = del->next;
	del->next->prev = del->prev;
	del->prev = del->next = NULL;
	free(del->data);
	free(del);

	return 0;
}

// 遍历
void llist_traval(const llisthead_t *h, pri_t pri)
{
	struct node_st *cur;	

	for (cur=h->head.next; cur != &h->head; cur = cur->next) {
		pri(cur->data);
	}
}

// 销毁
void llist_destroy(llisthead_t *h)
{
	struct node_st *cur, *n;	

	for (cur=h->head.next, n=cur->next; cur != &h->head; cur=n, n=n->next ) {
		free(cur->data);	
		cur->data = NULL;
		free(cur);
	}
	free(h);
}

