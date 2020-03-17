#include <iostream>

int main(void)
{
	// int *p = malloc(sizeof(int));
	int *p = new int; // 分配了４个字节存储空间
	*p = 20;
	std::cout << *p << endl;

	delete p;

	p = new int[100];

	delete[] p;

	return 0;
}

