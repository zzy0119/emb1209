#include <iostream>
#include <string.h>

using namespace std;
// 默认参数函数 必须在最后
void func(int n, int grade=100, string city="北京")
{
	cout << n <<", "<< grade << ", " << city << endl; 
}

int main(void)
{
	func(1, 89, "新疆");	
	func(2);

	return 0;
}
