#include <iostream>

using namespace std;

// 友元关系是单向的 友元关系不能传递

// 将一个类的成员函数作为另一个领的友元函数

class Address; // 声明类

class Student {
	private:
		const char *m_name;
		int m_id;
	public:
		Student(const char *name, int id);

		void show(Address *adr);
};

// 地址类
class Address {
	private:
		const char *m_province;
		const char *m_city;
	public:
		Address(const char *province, const char *city);

		// Student类作为Adress类的友元类
		friend class Student;
};

Student::Student(const char *name, int id) : m_name(name), m_id(id) {}

void Student::show(Address *adr)
{
	cout << "名字" << this->m_name << " id" << this->m_id << endl;
	cout << adr->m_province << "省" << adr->m_city << "市" << endl;
}

Address::Address(const char *province, const char *city)
{
	m_province = province;
	m_city = city;
}

int main(void)
{
	Student stu("小贝", 1);
	Address addr("吉林", "长春");

	stu.show(&addr);

	return 0;
}

