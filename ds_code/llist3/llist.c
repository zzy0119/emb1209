#include "llist.h"

// 函数接口
int llisthead_init(node_t *head)
{
	head->prev = head->next = head;
	return 0;
}

static int insert(node_t *newnode, node_t *p, node_t *n)
{
	newnode->prev = p;
	newnode->next = n;
	p->next = newnode;
	n->prev = newnode;
}

// 插入
int llist_insert_head(node_t *head, node_t *newnode)
{
	insert(newnode, head, head->next);	
	return 0;
}

int llist_insert_tail(node_t *head, node_t *newnode)
{
	insert(newnode, head->prev, head);
	return 0;
}

// 删除
int llist_delete(node_t *delnode)
{
	delnode->prev->next = delnode->next;
	delnode->next->prev = delnode->prev;
	delnode->prev = delnode->next = NULL;
}


