#include <iostream>

using namespace std;

// 基类
class Person {
	protected:
		const char *m_name;
		int m_age;
	public:
		Person(const char *name, int age);	
		virtual void show();
};

Person::Person(const char *name, int age) : m_name(name), m_age(age) {}
void Person::show()
{
	cout << m_name << "今年" << m_age << "岁了，他是一个自由工作者"	<< endl;
}

// 派生类 Teacher
class Teacher : public Person {
	private:
		int m_salary;
	public:
		Teacher(const char *name, int age, int salary);
		virtual void show(); // 声明为虚函数
};

Teacher::Teacher(const char *name, int age, int salary) : Person(name, age), \
															  m_salary(salary) {}
void Teacher::show()
{
	cout << m_name << "今年" << m_age << "岁了，他是一名老师，每个月赚" \
		<< m_salary << "钱" << endl;
}

int main(void)
{
	// 基类指针指向基类对象，调用基类成员函数
	Person *t = new Person("沈东", 20);
	t->show();

	// 基类指针指向派生类对象，调用派生类成员函数 ---->多态
	t = new Teacher("英杰", 30, 100000);
	t->show();

	return 0;
}


