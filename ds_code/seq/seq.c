#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "seq.h"

// 构建线性表头
seq_t *seqlist_init(int size)
{
	seq_t *me = NULL;
	
	me = malloc(sizeof(seq_t)); // sizeof(*me)
	if (NULL == me)
		return me;
	me->p = NULL;
	me->size = size; 
	me->nmemb = 0;

	return me;
}

// 增
int seqlist_add(seq_t *seqlist, const void *data)
{
	// 为新元素开辟存储空间----> 将新元素拷贝	
	seqlist->p = realloc(seqlist->p, (seqlist->nmemb+1) * seqlist->size);
	if (NULL == seqlist->p)
		return 1;
	memcpy((char *)(seqlist->p)+seqlist->nmemb * seqlist->size, data, seqlist->size);
	seqlist->nmemb ++;

	return 0;
}

// 查
void *seqlist_find(const seq_t *seqlist, const void *key, cmp_t cmp)
{
	for (int i = 0; i < seqlist->nmemb; i++) {
		if (cmp((char *)seqlist->p+i*seqlist->size, key) == 0) 
			return (char *)seqlist->p+i*seqlist->size;
	}

	return NULL;
}

// 删
int seqlist_del(seq_t *seqlist, const void *key, cmp_t cmp)
{
	char *f, *next;

	f = seqlist_find(seqlist, key, cmp);
	if (NULL == f)
		return 1;
	next = f+seqlist->size;
	memmove(f, next, seqlist->nmemb*seqlist->size-(next-(char *)seqlist->p));
	seqlist->nmemb --;
	seqlist->p = realloc(seqlist->p, seqlist->nmemb*seqlist->size);
	if (NULL == seqlist->p)
		return 1;

	return 0;
}

// 改
int seqlist_update(seq_t *seqlist, const void *key, cmp_t cmp, const void *newdata)
{
	void *f;

	f = seqlist_find(seqlist, key, cmp);
	if (NULL == f)
		return 1;
	memcpy(f, newdata, seqlist->size);

	return 0;
}

void seqlist_traval(const seq_t *seqlist, void (*pri)(const void *data))
{
	for (int i = 0; i < seqlist->nmemb; i++) {
		pri((char *)(seqlist->p)+i*seqlist->size);
	}
}

