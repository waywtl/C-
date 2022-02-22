#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//函数模板
template<class T>
T Add(T& x, T& y)
{
	return x + y;
}
//类模板
template<class T>
class Stack
{
public:
	Stack(int capacity = 4)
		:_top(0)
		, _capacity(capacity)
	{
		_a = new T[capacity];
	}

	~Stack()
	{
		delete[] _a; 
		_top = 0;
		_capacity = 0;
	}

	void Push(const T& x);
private:
	T* _a;
	int _top;
	int _capacity;
};

template<class T>
void Stack<T>::Push(const T& x)
{
	//...
}