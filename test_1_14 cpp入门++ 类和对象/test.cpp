#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//auto�ؼ��֡������Զ�ʶ������
//int main()
//{
//	//const int a = 10;
//	//auto& b = a;
//	//b = 20;
//
//	int a = 10;
//	auto b = a;
//	b = 20;
//
//	return 0;
//}

//��Χforѭ��
//�˴� a �˻�Ϊָ�룬����������
//void TestFor(int a[])
//{
//	for (auto& e : a)
//		cout << e << endl;
//}

//int main()
//{
//	int arr[] = { 1,2,3,4,5 };
//	//for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
//	//{
//	//	cout << arr[i] << endl;
//	//}
//
//	//���ΰ�arr[0]��arr[1]...��ֵ��e
//	//for (auto e : arr)
//	//{
//	//	cout << e << endl;
//	//}
//
//	for (auto& e : arr)
//	{
//		e += 1;
//	}
//	for (auto e : arr)
//	{
//		cout << e << endl;
//	}
//	return 0;
//}

//��ָ��Ϊnullptr
//int main()
//{
//	//����������ͬ��
//	//#ifndef NULL
//    //#ifdef __cplusplus
//    //#define NULL 0
//    //#else
//    //#define NULL ((void *)0)
//    //#endif
//    //#endif
//    //c++98/c++03
//	int* p1 = NULL;
//	int* p2 = 0;
//
//    //c++11
//    //���Ƽ���������
//    int* p3 = nullptr;
//	return 0;
//}

#include <string>

class Student
{
public:
    void Init(const char* name, int age, int id)
    {
        strcpy(_name, name);
        _age = age;
        _id = id;
    }

    void Print()
    {
        cout << _name << "   ";
        cout << _age << "   ";
        cout << _id << "   " << endl;
    }
//private:
    char* _name;
    int _age;
    int _id;
};

int main()
{
    Student s1;
    Student s2;
    s1.Init("����", 18, 1);
    s2.Init("����", 19, 2);
    s1.Print();
    s2.Print();
    return 0;
}