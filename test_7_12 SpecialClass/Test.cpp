#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

//1.�����һ���ֻ࣬���ڶ��ϴ�������
//class HeapOnly
//{
//public:
//	static HeapOnly* CreateObj()
//	{
//		return new HeapOnly;
//	}
//
//	HeapOnly(const HeapOnly& ho) = delete;
//private:
//	HeapOnly()
//		:_a(0)
//	{}
//
//	HeapOnly(const HeapOnly& ho);
//private:
//	int _a;
//};
//
//int main()
//{
//	//HeapOnly ho1;
//	//HeapOnly* pho = new HeapOnly;
//	HeapOnly* pho = HeapOnly::CreateObj();
//	//HeapOnly ho2(*pho);
//	return 0;
//}

//2.�����һ���ֻ࣬����ջ�ϴ�������
//����һ:�����캯��˽�У���һ����̬��Ա������������
//ȱ�ݣ���ֹ����newһ������ʱʹ�ÿ������죬�����ǲ��ܽ���������delete
//class StackOnly
//{
//public:
//	static StackOnly CreateObj()
//	{
//		return StackOnly();
//	}
//
//	//StackOnly(const StackOnly& so) = delete;
//private:
//	StackOnly()
//		:_a(0)
//	{}
//private:
//	int _a;
//};
//
//int main()
//{
//	StackOnly so1 = StackOnly::CreateObj();
//	//StackOnly* pso = new StackOnly;
//	StackOnly* pso = new StackOnly(so1);
//
//	return 0;
//}

//�����������ε��ײ��operator new
//class StackOnly
//{
//public:
//	void* operator new(size_t size) = delete;
//	void operator delete(void* ptr) = delete;
//private:
//	int _a;
//};
//
//int main()
//{
//	StackOnly so1;
//	//StackOnly* pso = new StackOnly;
//	return 0;
//}

//3.�����һ���࣬���ܱ�����
//����ֻ�ᷢ���ڿ�������͸�ֵ�����������μ���
//class CopyBan
//{
//public:
//	CopyBan(int a = 0)
//		:_a(a)
//	{}
//
//	CopyBan(const CopyBan& cb) = delete;
//	CopyBan& operator=(const CopyBan& cb) = delete;
//private:
//	int _a;
//};
//
//int main()
//{
//	CopyBan cb1(1);
//	//CopyBan cb2(cb1);
//	CopyBan cb2;
//	//cb2 = cb1;
//	return 0;
//}

//4.�����һ���࣬���ܱ��̳�
//C++98
//class InheritBan
//{
//	static InheritBan CreatObj()
//	{
//		return InheritBan();
//	}
//private:
//	InheritBan()
//	{}
//};

//C++11
//class InheritBan final
//{
//	//...
//};

//5.�����һ���ֻ࣬�ܴ���һ������(����ģʽ)
//����ģʽ
//
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		return &_instance;
//	}
//private:
//	Singleton()
//	{}
//
//	Singleton(const Singleton& s) = delete;
//	Singleton& operator=(const Singleton& s) = delete;
//private:
//	static Singleton _instance;
//};
//
//Singleton Singleton::_instance;

//����ģʽ
//�����ִ氲ȫ���⣬��Ҫ����

//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		//˫�жϣ�����Ƶ����������Դ
//		if (_pInstance == nullptr)
//		{
//			std::unique_lock<mutex> lock(_mtx);
//			if (_pInstance == nullptr)
//			{
//				_pInstance = new Singleton;
//			}
//		}
//		return _pInstance;
//	}
//private:
//	Singleton()
//	{}
//
//	Singleton(const Singleton& s) = delete;
//	Singleton& operator=(const Singleton& s) = delete;
//private:
//	static Singleton* _pInstance;
//	static mutex _mtx;
//}; 
//
//Singleton* Singleton::_pInstance = nullptr;
//mutex Singleton::_mtx;

//��������һ��ʵ�ַ�ʽ
//��C++98�У����ڹ��캯�����̰߳�ȫ���⣻
//��C++11��û����
class Singleton
{
public:
	static Singleton& GetInstance()
	{
		static Singleton instance;
		return instance;
	}
private:
	Singleton()
	{}

	Singleton(const Singleton& s) = delete;
	Singleton& operator=(const Singleton& s) = delete;
};