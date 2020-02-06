#ifndef __LLIST_H
#define __LLIST_H

/*
 双向环链
 */
typedef struct node_st {
	struct node_st *prev; // 前驱地址
	struct node_st *next; // 后继地址
}node_t;


// 函数接口
int llisthead_init(node_t *head);

// 插入
int llist_insert_head(node_t *head, node_t *newnode);

int llist_insert_tail(node_t *head, node_t *newnode);

// 删除
int llist_delete(node_t *delnode);

#endif

