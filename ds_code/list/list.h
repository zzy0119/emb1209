#ifndef __LIST_H
#define __LIST_H

// 抽象数据类型
// 结点
struct node_st {
	void *data; // 存放结点数据的地址
	struct node_st *next; // 指针域:下一个结点的地址
};

// 头结点
typedef struct {
	// struct node_st *next; // 第一个结点地址
	struct node_st headnode;
	int size; // 数据域字节个数
}head_t;

enum {
	HEAD_INSERT=1,
	TAIL_INSERT
};

// 接口函数
typedef int (*cmp_t)(const void *data, const void *key);
typedef void (*pri_t)(const void *data);

// 创建头结点
int listhead_init(int size, head_t **head);

// 插入
int list_insert(head_t *head, const void *data, int way);

// 删除
int list_delete(head_t *head, const void *key, cmp_t cmp);

// 查找
void *list_find(const head_t *head, const void *key, cmp_t cmp);

// 遍历
void list_traval(const head_t *head, pri_t pri);

// 销毁
void list_destroy(head_t *head);

// 是否带环
int list_circle(const head_t *head);

#endif
