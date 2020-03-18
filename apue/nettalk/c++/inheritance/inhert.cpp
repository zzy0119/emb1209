#include <iostream>

using namespace std;

/*
 继承就是一个类从另一个类获取成员变量和成员函数的过程(inheritance)
 c++中，派生(Derive)和继承是一个意思
 派生父派生给子 继承子继承于父
 B类继承于A类
 A类称为父类或基类　B类称为子类或派生类
 */
class Person {
	// private:
	protected:
		char *m_name;
		int m_age;
	public:
		void setName(char *name);
		void setAge(int age);
		char *getName();
		int getAge();

		void show();
};

void Person::setName(char *name)
{
	this->m_name = name;
}

void Person::setAge(int age)
{
	this->m_age = age;
}

char *Person::getName()
{
	return this->m_name;
}

int Person::getAge()
{
	return this->m_age;
}

void Person::show()
{
	cout << this->m_name << "  " <<this->m_age << endl;
}
/*
  继承方式	public成员	protected成员　private成员
  public	public		protected		不可见
  protected	protected	protected		不可见
  private	private		private			不可见
  */

// 学生类继承Person类
class Student: public Person {
	private:
		float m_score;
	public:
		void setScore(int score);
		int getScore();

		void show(); //遮蔽父类方法
};

void Student::show()
{
	cout << m_score << endl;
}

void Student::setScore(int score)
{
	cout << this->m_name << endl;
	this->m_score = score;
}

int Student::getScore()
{
	return this->m_score;
}

int main(void)
{
	Student stu;	

	stu.setName("小白");
	stu.setAge(20);
	stu.setScore(100);

	cout << stu.getName() << endl;
	cout << stu.getAge() << endl;
	cout << stu.getScore() << endl;
	stu.show();

	return 0;
}

