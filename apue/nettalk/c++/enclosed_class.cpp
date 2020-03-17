#include <iostream>

using namespace std;

// 轮胎类 r w
class Tyre {
	private:
		int m_radius;
		int m_width;
	public:
		// 构造方法	
		Tyre(int r, int w);
		void show();
};

// 初始化列表
Tyre::Tyre(int r, int w) : m_radius(r), m_width(w){	
}

void  Tyre::show()
{
	cout << "轮胎半径是:" << m_radius << endl;
	cout << "轮胎宽度:" << m_width << endl;
}

// 引擎类
class Engine {
	private:
		float m_displacement;
	public:
		Engine(float ds=2.0);
		void show();
};

Engine::Engine(float ds) : m_displacement(ds) {}

void Engine::show()
{
	cout << "排量:" << m_displacement << endl;
}


// 车类
class Car {
	private:
		Tyre m_tyre;
		Engine m_engine;
		float m_price;
	public:
		Car(float price, int r, int w, int d=2.0);
		void show();
};

// Car封闭类　包含成员对象　初始化列表形式给成员对象构造方法传参数
Car::Car(float price, int r, int w, int d) : m_price(price), m_tyre(r, w), \
m_engine(d){}

void Car::show()
{
	cout << "价格" << m_price << "万" << endl;
	m_tyre.show();
	m_engine.show();
}

int main(void)
{
	Car car(20, 20, 300);

	car.show();

	return 0;
}

