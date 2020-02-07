#include <stdlib.h>

#include "student.h"

// 初始化学生管理系统结构
void sys_init(sys_student *s)
{
	INIT_LIST_HEAD(s);
}

// 增加
int sys_add_stu(sys_student *s, struct stu_st stu)
{
	struct node_st *newnode;

	newnode = malloc(sizeof(struct node_st));
	if (NULL == newnode)
		return -1;
	newnode->stu = stu;
	list_add_tail(&newnode->node, s);

	return 0;
}

// 删除 所有
int sys_del_stu(sys_student *s, const void *key, cmp_t cmp)
{
	struct list_head *p, *n;	
	struct node_st *cur;

	list_for_each_safe(p, n, s) {
		cur = list_entry(p, struct node_st, node);	
		if (cmp(&cur->stu, key) == 0) {
			list_del(p);
			free(cur);
		}
	}
	return 0;
}

// 查找
struct stu_st sys_search_stu(const sys_student *s, const void *key, cmp_t cmp);

// 学生总数
int sys_sum_stu(const sys_student *s);

// 销毁
void sys_destroy(sys_student *s);
