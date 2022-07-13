#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

//1.请设计一个类，只能在堆上创建对象
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

//2.请设计一个类，只能在栈上创建对象
//方法一:将构造函数私有，用一个静态成员函数创建对象
//缺陷：阻止不了new一个对象时使用拷贝构造，而我们不能将拷贝构造delete
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

//方法二：屏蔽掉底层的operator new
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

//3.请设计一个类，不能被拷贝
//拷贝只会发生在拷贝构造和赋值，将他们屏蔽即可
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

//4.请设计一个类，不能被继承
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

//5.请设计一个类，只能创建一个对象(单例模式)
//饿汉模式
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

//懒汉模式
//存在现存安全问题，需要加锁

//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		//双判断，避免频繁争用锁资源
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

//懒汉的另一种实现方式
//在C++98中，存在构造函数的线程安全问题；
//在C++11中没问题
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