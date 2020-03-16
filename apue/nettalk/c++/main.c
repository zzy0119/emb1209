#include <stdio.h>
#include <string.h>

#define NAMESIZE	32

struct student {
	int id;
	char name[NAMESIZE];
};

// 显示结构变量
static void show(struct student st)
{
	printf("%d %s\n", st.id, st.name);
}

int main(void)
{
	struct student stu;

	strcpy(stu.name, "hello");
	stu.id = 1;

	show(stu);

	return 0;
}

