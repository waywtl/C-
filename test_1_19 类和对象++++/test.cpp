#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//��ʼ���б�
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
//	//��ʼ���б���Ա��������ĵط�,���Ƽ��ڳ�ʼ���б���Ա������ʼ��
//	//��Ҫ�ڶ���ʱ��ʼ���ı�����Ҫ�ڴ˳�ʼ��
//	//const���������ã�û��Ĭ�Ϲ��캯�����Զ�������
//	//���ʼ����˳���ɶ���ʱ��˳����������ʼ���б��˳���޹�
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

//explicit�ؼ���
//class Date
//{
//public:
//	Date(int year)
//		: _year(year)
//	{}
//
//	//explicit�ؼ��ֿ��Խ�ֹ��ʽ����ת��
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
//	Date d2 = 2022;//��ʽ����ת��
//	return 0;
//}

//static��Ա
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
//	//��̬��Ա����,û��thisָ�룬ֻ�ܷ��ʾ�̬��Ա�����ͳ�Ա����
//	static int GetCount()
//	{
//		return _sCount;
//	}
//private:
//	int _a;
//
//	//��̬��Ա�������������࣬���ж���
//	//����ĳ�Ա�����У�����������
//	static int _sCount;//����
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

//��Ա����ȱʡֵ
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
//	//����ڳ�ʼ���б�׶Σ�û�жԳ�Ա������ʼ�������ͻ�ʹ��ȱʡֵ
//	A()
//	{}
//private:
//	int _a1 = 0;   //�����Ǹ���Ա����ȱʡֵ�����ǳ�ʼ������Ϊ��������
//	B _bb1 = 10;
//	B _bb2 = B(20);
//	int* p = (int*)malloc(4 * 10);
//	int arr[5] = { 1,2,3,4,5 };
//
//	//���캯��������̬��Ա���ʲ��ܸ�ȱʡֵ,������������ȫ�ֶ����ʼ��
//	//static int _sCount = 0;
//};
//
//int main()
//{
//	A a;
//	return 0;
//}

//��Ԫ
//class Date;
//class Time
//{
//	friend class Date; // ����������Ϊʱ�������Ԫ�࣬
//	                   //�����������о�ֱ�ӷ���Time���е�˽�г�Ա����
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
//		// ֱ�ӷ���ʱ����˽�еĳ�Ա����
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

//�ڲ���
class A
{
public:
	//�ڲ���
	//1.�ڲ���B����ȫ�ֶ����ǻ���һ���ģ�ֻ�������ⲿ��A��������
	//2.�ڲ���B���������ⲿ��A����Ԫ
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