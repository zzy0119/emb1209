#include <iostream>

using namespace std;
/*
   类的定义
   成员变量（属性）
   成员函数（方法）
   对象实例化
 */

class Person {
	// 控制成员变量和成员函数的访问权限　public private protected
	/*
	 类内：public protected private 都可以访问
	 类外：只能访问public属性和方法, 不能访问private protected
	 */
	private:
		// Property
		const char *name;
		int m_age;
		int m_id;
		float m_score;

	public:
		// Method
		void say();
		void setName(const char *nm);
		void setAge(int a=18); // 申明指定默认参数值
		void setId(int i);
		void setScore(float sc);
};

// :: 域解析符		inline
void Person::say() 
{
	cout <<  name << "的年龄是" << m_age << "id是" << m_id << \
		"成绩是" << m_score << endl;
}

// 成员们函数实现
void Person::setName(const char *name)
{
	this->name = name;
}

void Person::setAge(int a)
{
	m_age = a;
}
void Person::setId(int i)
{
	m_id = i;
}
void Person::setScore(float sc)
{
	m_score = sc;
}

int main(void)
{
	// 实例化对象
	Person pson; // 栈
	Person *pPson = new Person; // malloc(sizeof(Person))

	pson.setName("张三");
	pson.setAge();
	pson.setId(5);
	pson.setScore(100);

	pson.say();

#if 0
	pson.name = "小明";
	pson.age = 18;
	pson.id = 5;
	pson.score = 100;

	pson.say();

	pPson->name = "小李";
	pPson->age = 20;
	pPson->id = 2;
	pPson->score = 99.9;
	pPson->say();
#endif

	delete pPson; // 对象销毁

	return 0;
}

