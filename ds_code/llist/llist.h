#ifndef __LLIST_H
#define __LLIST_H

/*
 双向环链
 */
struct node_st {
	struct node_st *prev; // 前驱地址
	struct node_st *next; // 后继地址
	void *data; // 数据地址
};

// 头结点
typedef struct {
	struct node_st head;
	int size;
}llisthead_t;

enum {
	INSERT_HEAD,
	INSERT_TAIL
};

typedef int (*cmp_t)(const void *data, const void *key);
typedef void (*pri_t)(const void *data);

// 函数接口
llisthead_t *llisthead_init(int size);

// 插入
int llist_insert(llisthead_t *head, const void *data, int way);

// 删除
int llist_delete(llisthead_t *head, const void *key, cmp_t cmp);

// 遍历
void llist_traval(const llisthead_t *head, pri_t pri);

// 销毁
void llist_destroy(llisthead_t *head);

#endif

