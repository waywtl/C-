#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

//C++��������
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

//ȱʡ����
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

//��������

//���ɺ������ص�����
//1.����������ͬ
//2.�������Ͳ�ͬ
//3.����˳��ͬ

//����
//int main()
//{
//	//1.���ñ����ڶ���ʱ��ʼ��
//	//int a = 10;
//	//int& b;
//
//	//2.һ�����������ж������
//	//int a = 10;
//	//int& b = a;
//	//int& c = a;
//	//int& d = b;
//
//	//double c = 1.1;
//
//	//3.����һ������һ��ʵ�壬�ٲ�����������ʵ��
//	int a = 10;
//	int& b = a;
//
//	int c = 20;
//	//�����ǰ�c��ֵ����b;
//	b = c;
//	return 0;
//}

//1.����������
//�����������ɺ�������
void Swap(int x, int y) //��ֵ
{
	int tmp = x;
	x = y;
	y = tmp;
}

void Swap(int* p1, int* p2) //����ַ
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void Swap(int& r1, int& r2) //������
{
	int tmp = r1;
	r1 = r2;
	r2 = tmp;
}

//2.����������ֵ
//��ǰ������ڵ�����
//1.���ڷǷ����ʣ���ΪAdd(1,2)�ķ���ֵ��c�����ã�Addջ֡���ٺ󣬻�ȥ����cλ�ÿռ�
//2.���Add����ջ֡���٣�����ռ䣬��ôȡcֵ�������ֵ����ret�������ֵ
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

