#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//运算符重载
//class Date
//{
//public:
//	Date(int year = 0, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
////private:
//	int _year;
//	int _month;
//	int _day;
//};
//
////定义在类外
//bool operator>(const Date& d1, const Date& d2)
//{
//	if (d1._year > d2._year)
//	{
//		return true;
//	}
//	else if (d1._year == d2._year && d1._month > d2._month)
//	{
//		return true;
//	}
//	else if (d1._year == d2._year && d1._month == d2._month && d1._day > d2._day)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//int main()
//{
//	Date d1(2022,1,16);
//	Date d2(2022,1,31);
//
//	d1 > d2; //实际 ->operator>(d1, d2);
//	operator>(d1, d2);
//	return 0;
//}

//class Date
//{
//public:
//	Date(int year = 0, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	//定义在类里，由于有隐藏this指针
//	//实际为 bool operator>(Date* const this,const Date& d)
//	bool operator>(const Date& d)
//	{
//		if (_year > d._year)
//		{
//			return true;
//		}
//		else if (_year == d._year && _month > d._month)
//		{
//			return true;
//		}
//		else if (_year == d._year && _month == d._month && _day > d._day)
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	Date d1(2022, 1, 16);
//	Date d2(2022, 1, 31);
//
//	d1 > d2; //实际  d1.operator>(d2);
//  d1.operator>(d2);
//	return 0;
//}

//赋值运算符重载
//若未显示定义，编译器也会生成一个,跟拷贝构造做的事完全类似
class Date
{
public:
	Date(int year = 0, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	Date& operator=(const Date& d)
	{
		//自己给自己赋值就不用处理
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1;
	Date d2(2022, 1, 16);
	//一个已经存在的对象拷贝初始化一个马上创建实例化的对象
	Date d3(d2);//拷贝构造
	Date d4 = d2;//拷贝构造

	//两个已经存在的对象之间进行赋值拷贝
	d3 = d1 = d2; //  d1.operator=(d2);
	return 0;
}