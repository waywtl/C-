#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//����thisָ��
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

//���Ĭ�ϳ�Ա����
//���캯��������ʼ��������Init
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
//	//д��ȫȱʡ�������ȱʡ��������
//  //��ʵ��������ʱ����
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

//��������������Դ��������destory
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
//	//��������,�ڶ�����������ڽ���ʱ�Զ�����
//	//��Ĭ�Ϲ��캯��һ��
//	//�������ͳ�Ա�����������Զ������ͳ�Ա��������������������
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

//�������캯��
//�ǹ��캯�������غ���������ʾ���壬�򲻻�����Ĭ�Ϲ��캯��������Ҳ����ʾ����
//��δ��ʾ���壬Ĭ�Ͽ������캯���ᰴ�ֽڽ���ǳ����(ֵ�Ŀ���)
//��Ҫ���ʱ���������캯����Ҫ������ʾ����
//�������ͳ�Ա�����ᰴ�ֽڽ���ǳ����(ֵ�Ŀ���)
//�Զ������ͳ�Ա�����������Ŀ������캯��
class Date
{
public:
	Date(int year = 2022, int month = 1, int day = 15)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	//�β�Ϊ���ã�����ᵼ������ݹ����
	//��Ϊ��Ϊ��ֵ���Σ��βεĿ���Ҳ��һ�ο�������
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