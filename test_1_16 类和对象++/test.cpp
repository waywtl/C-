#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//���������
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
////����������
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
//	d1 > d2; //ʵ�� ->operator>(d1, d2);
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
//	//�������������������thisָ��
//	//ʵ��Ϊ bool operator>(Date* const this,const Date& d)
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
//	d1 > d2; //ʵ��  d1.operator>(d2);
//  d1.operator>(d2);
//	return 0;
//}

//��ֵ���������
//��δ��ʾ���壬������Ҳ������һ��,������������������ȫ����
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
		//�Լ����Լ���ֵ�Ͳ��ô���
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
	//һ���Ѿ����ڵĶ��󿽱���ʼ��һ�����ϴ���ʵ�����Ķ���
	Date d3(d2);//��������
	Date d4 = d2;//��������

	//�����Ѿ����ڵĶ���֮����и�ֵ����
	d3 = d1 = d2; //  d1.operator=(d2);
	return 0;
}