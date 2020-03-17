#include <iostream>

using namespace std;

#define PI	3.14

class Circle {
	private:
		int m_r;
	public:
		// 构造方法 无返回值 必须声明成public
		Circle(int r);
		// 构造方法　可以重载
		Circle();
		float getGirth();
};

// 实现方法
Circle::Circle(int r)
{
	m_r = r;
}

Circle::Circle()
{
	cout << "Circle()" << endl;
	m_r = 0;
}

float Circle::getGirth()
{
	return 2*PI*m_r;		
}

int main(void)
{
	Circle c(3);
	Circle c2; // 不加括号

	Circle *p = new Circle; // 括号可加可不加

	cout << "周长是:" << c.getGirth() << endl;

	cout << "c2周长是" << c2.getGirth() << endl;

	return 0;
}

