#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <functional>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
using namespace std;

//包装器 
//int f(int a, int b)
//{
//	return a + b;
//}
//
//struct Functor
//{
//public:
//	int operator() (int a, int b)
//	{
//		return a + b;
//	}
//};
//
//class Plus
//{
//public:
//	static int plusi(int a, int b)
//	{
//		return a + b;
//	}
//	double plusd(double a, double b)
//	{
//		return a + b;
//	}
//};
//
//int main()
//{
//	function<int(int, int)> f1 = f;
//	function<int(int, int)> f2 = Functor();
//	//成员函数要加&
//	function<int(int, int)> f3 = &Plus::plusi;
//	//非静态成员函数要多加一个类型参数
//	function<double(Plus, double, double)> f4 = &Plus::plusd;
//
//    //bind绑定参数
//    function<double(double, double)> f5 = bind(&Plus::plusd, Plus(), placeholders::_1, placeholders::_2);
//
//	cout << f1(1, 2) << endl;
//	cout << f2(3, 4) << endl;
//	cout << f3(5, 6) << endl;
//	cout << f4(Plus(), 7, 8) << endl;
//	cout << f5(9, 10) << endl;
//	return 0;
//}
//
////逆波兰表达式求值
//class Solution {
//public:
//    int evalRPN(vector<string>& tokens)
//    {
//        map<string, function<int(int, int)>> opFuncMap;
//        opFuncMap["+"] = [](int a, int b)->int {return a + b; };
//        opFuncMap["-"] = [](int a, int b)->int {return a - b; };
//        opFuncMap["*"] = [](int a, int b)->int {return a * b; };
//        opFuncMap["/"] = [](int a, int b)->int {return a / b; };
//
//        stack<int> st;
//        for (const auto& str : tokens)
//        {
//            if (opFuncMap.find(str) != opFuncMap.end())
//            {
//                int right = st.top();
//                st.pop();
//                int left = st.top();
//                st.pop();
//
//                st.push(opFuncMap[str](left, right));
//            }
//            else
//            {
//                st.push(stoi(str));
//            }
//        }
//        return st.top();
//    }
//};

//线程库

//int x = 0;
//mutex mtx;
//
//void Func(int n)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		mtx.lock();
//		++x;
//		mtx.unlock();
//	}
//}
//
//int main()
//{
//	thread t1(Func, 10000);
//	thread t2(Func, 20000);
//
//	t1.join();
//	t2.join();
//
//	cout << x << endl;
//	return 0;
//}

//原子操作的++
//atomic<int> x = 0;
//
//void Func(int n)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		++x;
//	}
//}
//
//int main()
//{
//	thread t1(Func, 10000);
//	thread t2(Func, 20000);
//
//	t1.join();
//	t2.join();
//
//	cout << x << endl;
//	return 0;
//}

//左值引用传参
//void Func(int& x)
//{
//	x += 10;
//}
//
//int main()
//{
//	int n = 10;
//	//线程直接的函数的参数如果为左值引用，需要在传参时加std::ref(x)
//	thread t(Func, std::ref(n));
//	t.join();
//	cout << n << endl;
//	return 0;
//}

//void Func(vector<int>& v, int n, int base)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		v.push_back(base + i);
//	}
//}
//
//int main()
//{
//	vector<int> v;
//	thread t1(Func, std::ref(v), 1, 100);
//	thread t2(Func, std::ref(v), 1, 200);
//
//	t1.join();
//	t2.join();
//
//	for (auto e : v)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//	return 0;
//}


//lock_guard     unique_lock
//创建时申请锁，销毁时释放锁
//避免出现程序因抛异常而导致持有的锁没释放的问题
//template<class Lock>
//class LockGuard
//{
//public:
//	LockGuard(Lock lock)
//		:_lock(lock)
//	{
//		_lock.lock();
//	}
//
//	~LockGuard()
//	{
//		_lock.unlock()
//	}
//private:
//	Lock& _lock;
//};

//条件变量 condition_variable 需要配合unique_lock<mutex>使用
//因为cond本身就是临界资源,需要锁的保护


//两个线程交替打印
int main()
{
	int n = 100;
	int i = 0;
	mutex mtx;
	condition_variable cond;
	bool flag = false;

	//打印偶数，先打印
	thread t1([&, n] 
		{
			while (i < n)
			{
				unique_lock<mutex> lock(mtx);
				cond.wait(lock, [&flag] {return !flag; });

				cout << "I am t1, id is " << this_thread::get_id() << ":" << i << endl;
				++i;
				
				flag = !flag;
				cond.notify_one();
			}
		});
	//打印奇数，后打印
	thread t2([&, n]
		{
			while (i < n)
			{
				unique_lock<mutex> lock(mtx);
				cond.wait(lock, [&flag] {return flag; });

				cout << "I am t2，id is " << this_thread::get_id() << ":" << i << endl;
				++i;

				flag = !flag;
				cond.notify_one();
			}
		});

	t1.join();
	t2.join();
	return 0;
}