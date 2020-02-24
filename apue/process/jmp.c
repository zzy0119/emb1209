#include <stdio.h>
#include <setjmp.h>

static jmp_buf env;

static int div2num(int m, int n)
{
	if (n == 0) {
		longjmp(env, 2);	
	}

	return m / n;
}

int main(void)
{
	int num1, num2;

	printf("请输入两个整型数:");
	if (setjmp(env) != 0) 
		printf("请重新输入:");
	scanf("%d%d", &num1, &num2);

	printf("%d\n", div2num(num1, num2));

	return 0;
}
