#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
#define MUL(m, n) (m) * (n)

void get_memery(char **s)
{
	*s = malloc(10);
	if (NULL == *s)	
		return ;
	strncpy(*s, "hello", 6);
}

int main(void)
{
	char *p = NULL;
	char num[N] = {};

	int *m, n;

	get_memery(&p);
	puts(p);

	printf("%d\n", MUL(3+2, 6+2)); // 3+2*6+2
#if 0
	1. 用变量a给出下面的定义
		a) 一个整型数（An integer）
			int a;
		b) 一个指向整型数的指针（A pointer to an integer）
			int *a;
		c) 一个指向指针的的指针，它指向的指针是指向一个整型数（A pointer to a pointer to an integer）
			int **a;
		d) 一个有10个整型数的数组（An array of 10 integers）
			int a[10];
		e) 一个有10个指针的数组，该指针是指向一个整型数的（An array of 10 pointers to integers）
			int *a[10];
		f) 一个指向有10个整型数数组的指针（A pointer to an array of 10 integers）
			int (*a)[10];
		g) 一个指向函数的指针，该函数有一个整型参数并返回一个整型数（A pointer to a function that takes an integer as an argument and returns an integer）
			int (*a)(int);
		h) 一个有10个指针的数组，该指针指向一个函数，该函数有一个整型参数并返回一个整型数（ An array of ten pointers to functions that take an integer argument and return an integer ）
			int (*a[10])(int);
#endif

	return 0;
}
