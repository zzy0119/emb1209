#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	string s1;	
	string s2 = "hello";
	string s3 = s2;
	string s4("world");
	string s5(10, 's');

#if 0
	cout << s2.length() << endl;	

	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;

	// 转换为c风格字符串
	const char *cs = s2.c_str();
	cout << cs << endl;

	// 读入
	cin >> s1;
	cout << s1 << endl;

	// 访问成员
	int len = s1.length();
	for (int i = 0; i < len; i++) {
		cout << s1[i];
	}
	cout << endl;

	// 字符串拼接
	s2 += s1;
	cout << s2 << endl;

	// 增删该查
	s2.insert(0, "add");
	cout << s2 << endl;
	s2.insert(2, "two");
	cout << s2 << endl;

	s2.erase(3, 5); // .erase(pos, len);
	cout << s2 << endl;

	// 获取子串
	s1 = s2.substr(2, 5); // .substr(pos, len);
	cout << s1 << endl;
#endif
	
	// 查找
	s1 = "i love china";	
	s2 = "love";
	int ind;
	
	ind = s1.find(s2, 5); // .find(substr, start_index)
	cout << ind << endl;

	return 0;
}

