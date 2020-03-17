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
		void show() const; // const 成员函数
		void setName(const char *nm);

		// 静态成员函数 :　没有this指针的 只能访问静态成员变量
		static int getTotal();
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

void Student::show() const
{
	cout << this->m_name << " " << this->m_age << "(当前共有" << m_total << "名学生)" << endl;
}

void Student::setName(const char *nm)
{
	this->m_name = nm;
}

int main(void)
{
	Student stu1("小ａ", 19);
	// 匿名对象
	stu1.show();
	(new Student("小b", 20))->show();

	cout << Student::getTotal() << endl;

	// 常对象 只能调用const成员
	const Student stu3("小c", 11);
	Student const stu4("小d", 9);

	stu3.show();
	// stu3.setName("小e");
	stu3.show();

	return 0;
}

