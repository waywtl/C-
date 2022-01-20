#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

//new delete
//int main()
//{
//	//malloc free
//	//int* p1 = (int*)malloc(sizeof(int));
//	//int* p2 = (int*)malloc(sizeof(int)*4);
//
//	//free(p1);
//	//free(p2);
//
//	//new delete
//	int* p3 = new int;
//	int* p4 = new int[4];
//
//	delete p3;
//	delete[] p4;
//
//	return 0;
//}

//C++提出new和delete,主要解决两个问题
//1.自定义类型对象自动申请的时候，初始化和清理的问题
//  new和delete会调用构造和析构函数
//2.new失败了以后要求抛异常，这样才符合面向对象语言的出错处理机制
//ps:delete和free一般不会失败，如果失败了，都是释放空间上存在越界或者释放指针位置不对
class A
{
public:
	A(int a = 10)
		:_a(a)
	{
		cout << "A(int a = 10)" << endl;
	}

	~A()
	{
		cout << "~A()" << endl;
	}
private:
	int _a;
};

int main()
{
	A* p1 = new A(20);
	A* p2 = new A[4]{10,20,30,40};

	delete p1;
	delete[] p2;
	return 0;
}