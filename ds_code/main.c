#include <stdio.h>
#include <string.h>
#include "seq.h"

#define NAMESIZE	32

struct stu_st {
	int id;
	char name[NAMESIZE];
};

void show(const void *data)
{
	const struct stu_st *d = data;
	printf("%d %s\n", d->id, d->name);
}

int cmp_name(const void *data, const void *key)
{
	const struct stu_st *d = data;
	const char *k = key;

	return strcmp(d->name, k);
}

int cmp_int(const void *data, const void *key)
{
	const struct stu_st *d = data;
	const int *k = key;

	return d->id - *k;
}

int main(void)
{
	seq_t *list;
	struct stu_st stu;
	// 构建表
	list = seqlist_init(sizeof(struct stu_st));

	// 插入元素
	stu.id = 1;
	strcpy(stu.name, "王书静");
	seqlist_add(list, &stu);
	stu.id = 2;
	strcpy(stu.name, "武靖森");
	seqlist_add(list, &stu);
	stu.id = 3;
	strcpy(stu.name, "任树淇");
	seqlist_add(list, &stu);

	seqlist_traval(list, show);
	// 删除
	char *delname = "武靖森";
	seqlist_del(list, delname, cmp_name);

	int id = 3;
	seqlist_del(list, &id, cmp_int);

	// 遍历
	seqlist_traval(list, show);

	return 0;
}
