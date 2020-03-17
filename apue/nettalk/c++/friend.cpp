#include <iostream>

using namespace std;

class Student {
	private:
		const char *m_name;
		int m_age;
	private:
		static int m_total; // 静态成员变量
	public:
		Student(const char *name, int age);
		void setName(const char *nm);

		// 静态成员函数 :　没有this指针的 只能访问静态成员变量
		static int getTotal();

		// 友元函数
		friend void show(Student *p);
};

// 初始化静态变量 !!!!必有的
int Student::m_total = 0;

Student::Student(const char *name, int age):m_name(name), m_age(age)
{
	m_total ++;
}

int Student::getTotal()
{
	return m_total;
}

void show(Student *stu)
{
	cout << stu->m_name << "," << stu->m_age << endl; 
}

void Student::setName(const char *nm)
{
	this->m_name = nm;
}

int main(void)
{
	Student *p = new Student("小王", 25);

	show(p);

	return 0;
}

