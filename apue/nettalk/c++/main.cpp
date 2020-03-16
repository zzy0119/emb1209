#include <stdio.h>
#include <string.h>
// 类 

namespace Zzy{
	class Student {
		public:
			// 描述类属性
			int id;
			char name[32];

			// 描述行为--->方法
			void show() {
				printf("%d %s\n", id, name);
			}
	};
}

int main(void)
{
	using namespace Zzy;

	// 实例化对象
	Student stu;

	stu.id = 1;
	strcpy(stu.name, "小白");

	stu.show();

	return 0;
}


