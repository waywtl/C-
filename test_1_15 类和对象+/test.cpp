#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//隐藏this指针
//class Date
//{
//public:
//  //void Init(Date* this, int year, int month, int day)
//	void Init(int year, int month, int day)
//	{
//		_year = year;   //this->_year = year;
//		_month = month; //this->_month = month;
//		_day = day;     //this->_day = day;
//	}
//
//  //void Print(Date* this)
//	void Print()
//	{
//	  //cout << this->_year << "." << this->_month << "." << this->_day << endl;
//		cout << _year << "." << _month << "." << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//int main()
//{
//	Date d1;
//	d1.Init(2022, 1, 15); //d1.Init(&d1,2022,1,15);
//	d1.Print(); //d1.Print(&d1);
//	return 0;
//}

//类的默认成员函数
//构造函数——初始化，类似Init
//class Date
//{
//public:
//	//Date()
//	//{
//	//	_year = 2022;
//	//	_month = 1;
//	//	_day = 15;
//	//}
//
//	//Date(int year, int month, int day)
//	//	{
//	//		_year = year;  
//	//		_month = month; 
//	//		_day = day;    
//	//	}
//
//	//写成全缺省参数或半缺省参数更好
//  //在实例化对象时调用
//	Date(int year = 2022, int month = 1, int day = 15)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//int main()
//{
//	Date d1;
//	Date d2(2022, 1, 15);
//	return 0;
//}

//析构函数——资源清理，类似destory
//class Date
//{
//public:
//	Date(int year = 2022, int month = 1, int day = 15)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	//析构函数,在对象的生命周期结束时自动调用
//	//与默认构造函数一样
//	//内置类型成员变量不处理，自定义类型成员变量调用他的析构函数
//	~Date()
//	{
//		;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//int main()
//{
//	Date d1;
//	Date d2(2022, 1, 15);
//	return 0;
//}

//class Stack
//{
//public:
//	Stack(int capacity = 4)
//	{
//		_a = (int*)malloc(sizeof(int) * capacity);
//		if (_a == nullptr)
//		{
//			cout << "malloc fail\n" << endl;
//			exit(-1);
//		}
//		_top = 0;
//		_capacity = capacity;
//	}
//
//	~Stack()
//	{
//		free(_a);
//		_a = nullptr;
//		_top = _capacity = 0;
//	}
//private:
//	int* _a;
//	int _top;
//	int _capacity;
//};
//
//int main()
//{
//	Stack s1;
//
//	return 0;
//}

//拷贝构造函数
//是构造函数的重载函数，若显示定义，则不会生成默认构造函数，后者也需显示定义
//若未显示定义，默认拷贝构造函数会按字节进行浅拷贝(值的拷贝)
//需要深拷贝时，拷贝构造函数需要我们显示定义
//内置类型成员变量会按字节进行浅拷贝(值的拷贝)
//自定义类型成员变量调用他的拷贝构造函数
class Date
{
public:
	Date(int year = 2022, int month = 1, int day = 15)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	//形参为引用，否则会导致无穷递归调用
	//因为若为传值传参，形参的拷贝也是一次拷贝构造
	Date(Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1;
	Date d2(d1);
	return 0;
}