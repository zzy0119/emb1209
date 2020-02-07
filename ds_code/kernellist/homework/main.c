#include <stdio.h>
#include <string.h>

#include <student.h>

enum {STU_INSERT=1, STU_DELETE, STU_TRAVAL, SYS_QUIT=9};

static void get_extra_ch()
{
	do {
		if(getchar() == '\n') 
			break;
	}while(1);

}


int main(void)
{
	sys_student sys;
	int choose;
	struct stu_st me;

	sys_init(&sys);

	while (1) {
		printf("*****嵌入式学生管理系统*****\n");	
		printf("1. 插入 2. 删除 3. 显示所有 9. 退出系统\n");
		scanf("%d", &choose);
		get_extra_ch();
		if (choose == SYS_QUIT)
			break;
		switch (choose) {
			case STU_INSERT:
				printf("请输入学生信息\n");
				printf("姓名: ");
				fgets(me.name, NAMESIZE, stdin);
				(me.name)[strlen(me.name)-1] = '\0';
				printf("年龄: ");
				scanf("%d", &me.age);
				get_extra_ch();
				printf("电话号: ");
				fgets(me.tel, TELLENGTH, stdin);	
				(me.tel)[strlen(me.tel)-1] = '\0';
				sys_add_stu(&sys, me);
				break;	
			case STU_DELETE:
				break;
			case STU_TRAVAL:
				sys_traval(&sys);
				break;	
			default:
				break;
		}
	}		

	return 0;
}

