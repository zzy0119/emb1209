#ifndef __SEQ_H
#define __SEQ_H

/*
 线性表
 	增删改查
 */

typedef struct seq_st {
	void *p;// 存放线性表首地址
	int size; // 存放表中每一个元素所占字节个数
	int nmemb; // 表中成员个数
}seq_t;

// 比较的函数指针类型
int (*cmp_t)(const void *data, const void *key);

// 构建线性表头
seq_t *seqlist_init(int size);

// 增
int seqlist_add(seq_t *seqlist, const void *data);

// 查
void *seqlist_find(const seq_t *seqlist, const void *key, cmp_t cmp);

// 删
int seqlist_del(seq_t *seqlist, const void *key, cmp_t cmp);

// 改
int seqlist_update(seq_t *seqlist, const void *key, cmp_t cmp, const void *newdata);

// 遍历
void seqlist_traval(const seq_t *seqlist, void (*pri)(const void *data));

#endif
