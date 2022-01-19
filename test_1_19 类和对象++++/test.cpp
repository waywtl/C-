#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//初始化列表
//class A
//{
//public:
//	A(int a)
//	{
//		_a = a;
//	}
//private:
//	int _a;
//};
//
//class Date
//{
//public:
//	//初始化列表，成员变量定义的地方,更推荐在初始化列表将成员变量初始化
//	//需要在定义时初始化的变量需要在此初始化
//	//const常量，引用，没有默认构造函数的自定义类型
//	//其初始化的顺序由定义时的顺序决定，与初始化列表的顺序无关
//	Date(int year, int month, int day,int i)
//		: _year(year)
//		, _month(month)
//		, _day(day)
//
//		,_N(10)
//		,_ref(i)
//		,_a(-1)
//	{}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//
//	const int _N;
//	int& _ref;
//	A _a;
//};
//
//int main()
//{
//	Date d1(2022, 1, 19, 1);
//
//	return 0;
//}

//explicit关键字
//class Date
//{
//public:
//	Date(int year)
//		: _year(year)
//	{}
//
//	//explicit关键字可以禁止隐式类型转换
//	//explicit Date(int year)
//	//	: _year(year)
//	//{}
//
//private:
//	int _year;
//};
//
//int main()
//{
//	Date d1(2022);
//	Date d2 = 2022;//隐式类型转换
//	return 0;
//}

//static成员
//class A
//{
//public:
//	A(int a = 0)
//		:_a(a)
//	{
//		++_sCount;
//	}
//
//	A(const A& aa)
//		:_a(aa._a)
//	{
//		++_sCount;
//	}
//
//	//静态成员函数,没有this指针，只能访问静态成员变量和成员函数
//	static int GetCount()
//	{
//		return _sCount;
//	}
//private:
//	int _a;
//
//	//静态成员变量属于整个类，所有对象
//	//在类的成员函数中，可以随便访问
//	static int _sCount;//声明
//};
//
//int A::_sCount = 0;
//
//int main()
//{
//	A a1;
//	A a2 = 1;
//	 
//	cout << a1.GetCount() << endl;
//	cout << A::GetCount() << endl;
//	return 0;
//}

//成员变量缺省值
//class B
//{
//public:
//	B(int b = 0)
//		:_b(b)
//	{}
//private:
//	int _b;
//};
//
//class A
//{
//public:
//	//如果在初始化列表阶段，没有对成员变量初始化，它就会使用缺省值
//	A()
//	{}
//private:
//	int _a1 = 0;   //这里是给成员变量缺省值，不是初始化，因为这里声明
//	B _bb1 = 10;
//	B _bb2 = B(20);
//	int* p = (int*)malloc(4 * 10);
//	int arr[5] = { 1,2,3,4,5 };
//
//	//构造函数不处理静态成员，故不能给缺省值,必须在类外面全局定义初始化
//	//static int _sCount = 0;
//};
//
//int main()
//{
//	A a;
//	return 0;
//}

//友元
//class Date;
//class Time
//{
//	friend class Date; // 声明日期类为时间类的友元类，
//	                   //则在日期类中就直接访问Time类中的私有成员变量
//public:
//	Time(int hour = 0, int minute = 0, int second = 0)
//		: _hour(hour)
//		, _minute(minute)
//		, _second(second)
//	{}
//private:
//	int _hour;
//	int _minute;
//	int _second;
//};
//class Date
//{
//public:
//	Date(int year = 1900, int month = 1, int day = 1)
//		: _year(year)
//		, _month(month)
//		, _day(day)
//	{}
//	void SetTimeOfDate(int hour, int minute, int second)
//	{
//		// 直接访问时间类私有的成员变量
//		_t._hour = hour;
//		_t._minute = minute;
//		_t._second = second;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//	Time _t;
//};
//
//int main()
//{
//	Date d1(2022, 1, 19);
//	d1.SetTimeOfDate(21, 17, 30);
//	return 0;
//}

//内部类
class A
{
public:
	//内部类
	//1.内部类B和在全局定义是基本一样的，只是它受外部类A类域限制
	//2.内部类B天生就是外部类A的友元
	class B
	{
	public:
		B(int b = 0)
			:_b(b)
		{}

		void f(const A& a)
		{
			cout << _k << endl;
			cout << a._a << endl;
		}
	private:
		int _b;
	};
private:
	static int _k;
	int _a = 1;
};

int A::_k = 0;

int main()
{
	A a;
	A::B b;
	b.f(a);
	return 0;
}