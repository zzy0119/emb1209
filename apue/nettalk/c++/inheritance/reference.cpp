#include <iostream>

using namespace std;

void swap2num(int *m, int *n)
{
	int t;

	t = *m;
	*m = *n;
	*n = t;
}

// 引用实现
int swap2num_r(int &m, int &n)
{
	int t;
	t = m;
	m = n;
	n = t;
}

int main(void)
{
	int num = 100;
	// 初始化引用　　定义引用& 使用不加&
	int &r = num; 
	int a = 10, b = 20;

	r = 96;

	cout << num << " " << r << endl;
	cout << &num << " " << &r << endl;

	swap2num(&a, &b);
	cout << a << " " << b << endl;

	swap2num_r(a, b);
	cout << a << " " << b << endl;

	return 0;
}


