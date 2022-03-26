#define _CRT_SECURE_NO_WARNINGS 1

namespace ljh
{
	template<class T>
	struct less
	{
		bool operator()(const T& left, const T& right)
		{
			return left < right;
		}
	};

	template<class T>
	struct greater
	{
		bool operator()(const T& left, const T& right)
		{
			return left > right;
		}
	};

	template<class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue
	{
	private:
		void adjust_up(int child)
		{
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				if (Compare()(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
					break;
			}
		}

		void adjust_down(int parent)
		{
			int child = parent * 2 + 1;
			while (child < _con.size())
			{
				if (child + 1 < _con.size() && Compare()(_con[child], _con[child+1]))
				{
					++child;
				}
				if (Compare()(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
					break;
			}
		}

	public:
		priority_queue()
			:_con()
		{}

		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
			:_con(first, last)
		{
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; --i)
			{
				adjust_down(i);
			}
		}

		void push(const T& x)
		{
			_con.push_back(x);
			adjust_up(_con.size() - 1);
		}

		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			adjust_down(0);
		}

		const T& top() const
		{
			return _con[0];
		}

		size_t size() const
		{
			return _con.size();
		}

		bool empty() const
		{
			return _con.empty();
		}

	private:
		Container _con;
	};
}