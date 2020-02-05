#include <stdlib.h>
#include <string.h>

#include "list.h"

int listhead_init(int size, head_t **head)
{
	head_t *h;	

	h = malloc(sizeof(head_t));
	if (NULL == h)
		return -1;
	h->size = size;
	h->headnode.next = NULL;
	h->headnode.data = NULL;

	*head = h;

	return 0;
}

// 插入
int list_insert(head_t *head, const void *data, int way)
{
	struct node_st *new;
	struct node_st *p;

	if (!(way == HEAD_INSERT || way == TAIL_INSERT))
		return -1;

	new = malloc(sizeof(struct node_st));
	if (NULL == new)
		return -1;
	new->data = calloc(1, head->size);
	memcpy(new->data, data, head->size);
	
	if (way == HEAD_INSERT) {
		new->next = head->headnode.next;
		head->headnode.next = new;
	} else {
		new->next = NULL;	
		for (p = &head->headnode; p->next != NULL;p = p->next) 
			;
		p->next = new;
	}

	return 0;
}

// 找到匹配的结点 前一个结点
static struct node_st *find_pre_node(const head_t *head, const void *key, cmp_t cmp)
{
	struct node_st *pre, *cur;	

	pre = &head->headnode;
	cur = pre->next;
	while (cur != NULL) {
		if (cmp(cur->data, key)	== 0) {
			return pre;		
		}
		pre = cur;
		cur = cur->next;
	}
	
	return NULL;
}

// 删除
int list_delete(head_t *head, const void *key, cmp_t cmp)
{
	struct node_st *pre, *del;	

	pre = find_pre_node(head, key, cmp);
	if (NULL == pre)
		return -1;
	del = pre->next;
	pre->next = del->next;
	del->next = NULL;

	free(del->data);
	free(del);	

	return 0;
}

// 查找
void *list_find(const head_t *head, const void *key, cmp_t cmp)
{
	struct node_st *pre;	

	pre = find_pre_node(head, key, cmp);
	if (NULL == pre)
		return NULL;
	return pre->next->data;
}

// 遍历
void list_traval(const head_t *head, pri_t pri)
{
	struct node_st *p;

	for (p = head->headnode.next; p != NULL; p = p->next)
		pri(p->data);
}

// 销毁
void list_destroy(head_t *head)
{
	struct node_st *n, *cur;

	for (cur=head->headnode.next, n=cur->next; ;) {
		free(cur->data);	
		free(cur);
		cur = n;
		if (cur == NULL)	
			break;
		n = cur->next;
	}

	free(head);
}


