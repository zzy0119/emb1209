#include <iostream>

using namespace std;

// 变长数组类
class VLA {
	private:
		const int m_len;
		int *m_arr; // 首地址
	public:
		VLA(int len);
		// 析构方法
		~VLA();
		int *getStartAddr();
};

// m_len　必须通过初始化列表形式给m_len赋值
VLA::VLA(int len):m_len(len)
{
	m_arr = new int[m_len];
}

VLA::~VLA()
{
	cout << "delete" << endl;
	delete[] m_arr;
}

int *VLA::getStartAddr()
{
	return m_arr;
}

int main(void)
{
	VLA *a = new VLA(10);
	int *p;

	p = a->getStartAddr();

	for (int i = 0; i < 10; i++) {
		p[i] = i+1;
		cout << p[i] << " ";
	}
	cout << endl;

	delete a;

	return 0;
}

