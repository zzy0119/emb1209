#ifndef __STUDENT_H
#define __STUDENT_H

#include "kernellist.h" 

// 学生管理系统
#define TELLENGTH	12
#define NAMESIZE 	32
struct stu_st {
	char name[NAMESIZE];
	int age;
	char tel[TELLENGTH];
};

struct node_st {
	struct stu_st stu;
	struct list_head node;
};

typedef struct list_head sys_student;
typedef int (*cmp_t)(const struct stu_st *data, const void *key);

// 接口
// 初始化学生管理系统结构
void sys_init(sys_student *s);

// 增加
int sys_add_stu(sys_student *s, struct stu_st stu);

// 删除 所有
int sys_del_stu(sys_student *s, const void *key, cmp_t cmp);

// 查找
struct stu_st sys_search_stu(const sys_student *s, const void *key, cmp_t cmp);

// 学生总数
int sys_sum_stu(const sys_student *s);

// 销毁
void sys_destroy(sys_student *s);

// 遍历
void sys_traval(const sys_student *s);

#endif

