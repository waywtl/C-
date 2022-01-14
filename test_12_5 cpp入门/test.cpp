#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

//C++输入和输出
//int main()
//{
//	int a;
//	double b;
//	char c;
//	cout << "Hello Bit!!" << endl;
//	cin >> a >> b;
//	cin >> c;
//	cout << a << endl << b << endl << c << endl;
//  return 0;
//}

//缺省参数
//void func(int a,int b = 10,int c = 20)
//{
//	cout << a << endl;
//	cout << b << endl;
//	cout << c << endl;
//}
//int main()
//{
//	func(0);
//	return 0;
//}

//函数重载

//构成函数重载的条件
//1.参数个数不同
//2.参数类型不同
//3.参数顺序不同

//引用
//int main()
//{
//	//1.引用必须在定义时初始化
//	//int a = 10;
//	//int& b;
//
//	//2.一个变量可以有多个引用
//	//int a = 10;
//	//int& b = a;
//	//int& c = a;
//	//int& d = b;
//
//	//double c = 1.1;
//
//	//3.引用一旦引用一个实体，再不能引用其他实体
//	int a = 10;
//	int& b = a;
//
//	int c = 20;
//	//这里是把c的值赋给b;
//	b = c;
//	return 0;
//}

//1.引用做参数
//他们三个构成函数重载
void Swap(int x, int y) //传值
{
	int tmp = x;
	x = y;
	y = tmp;
}

void Swap(int* p1, int* p2) //传地址
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void Swap(int& r1, int& r2) //传引用
{
	int tmp = r1;
	r1 = r2;
	r2 = tmp;
}

//2.引用做返回值
//当前代码存在的问题
//1.存在非法访问，因为Add(1,2)的返回值是c的引用，Add栈帧销毁后，会去访问c位置空间
//2.如果Add函数栈帧销毁，清理空间，那么取c值就是随机值，给ret就是随机值
//int& Add(int a, int b)
//{
//	int c = a + b;
//	return c;
//}
//
//int main()
//{
//	int& ret = Add(1, 2);
//	cout << ret << endl;
//	Add(10, 20);
//	cout << ret << endl;
//	return 0;
//}

