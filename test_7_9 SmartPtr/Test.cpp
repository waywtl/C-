#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

//智能指针
//RAII
//用起来像指针一样
//template<class T>
//class SmartPtr
//{
//public:
//	SmartPtr(T* ptr)
//		:_ptr(ptr)
//	{}
//
//	~SmartPtr()
//	{
//		delete _ptr;
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//	T* operator->()
//	{	
//		return _ptr;
//	}
//private:
//	T* _ptr;
//};

//智能指针发展史
//C++98 管理权转移 auto_ptr  
//会导致被拷贝的指针悬空，不推荐使用
//namespace ljh
//{
//	template<class T>
//	class auto_ptr
//	{
//	public:
//		auto_ptr(T* ptr)
//			:_ptr(ptr)
//		{}
//
//		auto_ptr(auto_ptr<T>& sp)
//			:_ptr(sp._ptr)
//		{
//			//管理权转移
//			sp._ptr = nullptr;
//		}
//
//		~auto_ptr()
//		{
//			if (_ptr)
//			{
//				delete _ptr;
//			}
//		}
//
//		T& operator*()
//		{
//			return *_ptr;
//		}
//
//		T* operator->()
//		{
//			return _ptr;
//		}
//	private:
//		T* _ptr;
//	};
//}

//boost库:scoped_ptr、shared_ptr、weak_ptr
//C++11:unique_ptr/scoped_ptr  -------> 防拷贝

namespace ljh
{
	template<class T>
	class default_delete
	{
	public:
		void operator()(const T* ptr)
		{
			cout << "delete: " << ptr << endl;
			delete ptr;
		}
	};

	template<class T>
	class default_array
	{
	public:
		void operator()(const T* ptr)
		{
			cout << "delete[]: " << ptr << endl;
			delete[] ptr;
		}
	};

	template<class T>
	class default_file
	{
	public:
		void operator()(FILE* ptr)
		{
			cout << "fclose: " << ptr << endl;
			fclose(ptr);
		}
	};

	template<class T, class D = default_delete<T>>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{}

		unique_ptr(const unique_ptr<T>& sp) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>& sp) = delete;

		~unique_ptr()
		{
			if (_ptr)
			{
				D del;
				del(_ptr);
			}
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};
}

//需要拷贝怎么办？
//增加引用计数
namespace ljh
{
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
			,_pRefCount(new int(1))
			,_pMtx(new mutex)
		{}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			,_pRefCount(sp._pRefCount)
			,_pMtx(sp._pMtx)
		{
			AddRef();
		}

		T* get() const 
		{
			return _ptr;
		}

		void Release()
		{
			_pMtx->lock();

			bool flag = false;
			if (--(*_pRefCount) == 0 && _ptr)
			{
				delete _ptr;
				delete _pRefCount;

				flag = true;
			}

			_pMtx->unlock();
			if (flag)
			{
				delete _pMtx;
			}
		}

		void AddRef()
		{
			_pMtx->lock();

			++(*_pRefCount);

			_pMtx->unlock();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (_ptr != sp._ptr)
			{
				Release();

				_ptr = sp._ptr;
				_pRefCount = sp._pRefCount;
				_pMtx = sp._pMtx;
				AddRef();
			}
			return *this;
		}

		~shared_ptr()
		{
			Release();
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
		int* _pRefCount;
		mutex* _pMtx;
	};

	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr()
			:_ptr(nullptr)
		{}

		weak_ptr(const weak_ptr<T>& sp)
			:_ptr(sp._ptr)
		{}

		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp.get())
		{}

		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp.get();

			return *this;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};
}

//struct Date
//{
//	int _year = 1;
//	int _month = 1;
//	int _day = 1;
//};
//
//void SharePtrFunc(ljh::shared_ptr<Date>& sp, size_t n, mutex& mtx)
//{
//	for (size_t i = 0; i < n; ++i)
//	{
//		// 这里智能指针拷贝会++计数，智能指针析构会--计数，这里是线程安全的。
//		ljh::shared_ptr<Date> copy(sp);
//		// 这里智能指针访问管理的资源，不是线程安全的。所以我们看看这些值两个线程++了2n次，但
//		//是最终看到的结果，并一定是加了2n
//
//		//如果要保证资源的线程安全，需要再加一把锁
//		{
//			unique_lock<mutex> lock(mtx);
//			copy->_year++;
//			copy->_month++;
//			copy->_day++;
//		}
//
//		//如果不想保证下面代码的线程安全，如何减小锁的力度？
//		//cout << "halo" << endl;
//	}
//}

//int main()
//{
//	ljh::shared_ptr<Date> p = new Date;
//	int n = 100;
//	mutex mtx;
//	thread t1(SharePtrFunc, std::ref(p), n, std::ref(mtx));
//	thread t2(SharePtrFunc, std::ref(p), n, std::ref(mtx));
//
//	t1.join();
//	t2.join();
//
//	cout << p->_year << endl;
//	cout << p->_month << endl;
//	cout << p->_day << endl;
//	return 0;
//}

//循环引用问题
//struct ListNode
//{
//	int _val;
//	//std::shared_ptr<ListNode> _next;
//	//std::shared_ptr<ListNode> _prev;
//
//	//使用weak_ptr来解决循环引用的问题
//	//原理：不增加引用计数
//	std::weak_ptr<ListNode> _next;
//	std::weak_ptr<ListNode> _prev;
//
//	~ListNode()
//	{
//		cout << "~ListNode()" << endl;
//	}
//};

//struct ListNode
//{
//	int _val;
//	ljh::weak_ptr<ListNode> _next;
//	ljh::weak_ptr<ListNode> _prev;
//
//	~ListNode()
//	{
//		cout << "~ListNode()" << endl;
//	}
//};
//
//int main()
//{
//	ljh::shared_ptr<ListNode> n1(new ListNode);
//	ljh::shared_ptr<ListNode> n2(new ListNode);
//
//	n1->_next = n2;
//	n2->_next = n1;
//	return 0;
//}

//如果指向一个数组，或者指向一个文件呢？如何析构？
//使用定制删除器

struct A
{
	~A()
	{
		cout << "~A()" << endl;
	}
};

int main()
{
	//定制删除器在类模板参数给 -- 类型
	ljh::unique_ptr<A> up1(new A);
	ljh::unique_ptr<A, ljh::default_array<A>> up2(new A[10]);
	ljh::unique_ptr<FILE, ljh::default_file<FILE>> up3(fopen("text.txt", "w"));

	//定制删除器在构造函数的参数给 -- 对象
	std::shared_ptr<A> sp1(new A);
	std::shared_ptr<A> sp2(new A[10], ljh::default_array<A>());
	std::shared_ptr<FILE> sp3(fopen("text.txt", "w"), ljh::default_file<FILE>());

	//使用lambda表达式取代仿函数
	std::shared_ptr<A> sp4(new A[10], [](A* p) {delete[] p; });
	std::shared_ptr<FILE> sp5(fopen("text.txt", "w"), [](FILE* p) {fclose(p); });
	return 0;
}