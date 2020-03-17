#include <iostream>

/*
 函数的重载规则
	1. 函数名一定要相同
	2. 参数列表必须不同(参数个数不同，类型不同，顺序不同)
	3. 返回值不作要求　可以相同也可以不同
	4. 如果只是返回值不同，不叫重载

 */

using namespace std;

void swap_2_num(int *m, int *n) 
{
	int t;	
	t = *m;
	*m = *n;
	*n = t;
}

void swap_2_num(float *m, float *n)
{
	float t;

	t = *m;
	*m = *n;
	*n = t;
}

int main(void)
{
	int a, b;
	float p, q;

	a = 10, b = 20;
	swap_2_num(&a, &b);

	p = 2.8, q = 3.9;
	swap_2_num(&p, &q);

	cout << a << b << endl;
	cout << p << q << endl;

	return 0;
}

