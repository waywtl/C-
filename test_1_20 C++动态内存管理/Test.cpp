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

//C++���new��delete,��Ҫ�����������
//1.�Զ������Ͷ����Զ������ʱ�򣬳�ʼ�������������
//  new��delete����ù������������
//2.newʧ�����Ժ�Ҫ�����쳣�������ŷ�������������Եĳ��������
//ps:delete��freeһ�㲻��ʧ�ܣ����ʧ���ˣ������ͷſռ��ϴ���Խ������ͷ�ָ��λ�ò���
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