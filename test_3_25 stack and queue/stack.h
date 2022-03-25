#define _CRT_SECURE_NO_WARNINGS 1

#pragma once

namespace ljh
{
	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}

		const T& top() const
		{
			return _con.back();
		}

		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}
	private:
		Container _con;
	};
}