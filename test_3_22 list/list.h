#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <assert.h>
namespace ljh
{
	template<class T>
	struct ListNode
	{
		ListNode<T>* _next;
		ListNode<T>* _prev;
		T _data;

		ListNode(const T& data = T())
			:_next(nullptr)
			,_prev(nullptr)
			,_data(data)
		{}
	};

	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef ListNode<T> Node;
		typedef __list_iterator<T, Ref, Ptr>  self;
		Node* _node;

		__list_iterator(Node* x)
			:_node(x)
		{}

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		self operator--(int)
		{
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const self& it)
		{
			return _node != it._node;
		}
	};

	template<class T>
	class list
	{
		typedef ListNode<T> Node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;

			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		list(const list<T>& lt)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;

			list<T> tmp(lt.begin(), lt.end());
			std::swap(_head, tmp._head);
		}

		list<T>& operator=(list<T> tmp)
		{
			std::swap(_head, tmp._head);
			return *this;
		}

		~list()
		{
			clear();

			delete[] _head;
			_head = nullptr;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				earse(it++);
			}
			_head->_next = _head;
			_head->_prev = _head;
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void push_back(const T& x)
		{
			/*Node* tail = _head->_prev;
			Node* newNode = new Node(x);
			newNode->_prev = tail;
			tail->_next = newNode;
			newNode->_next = _head;
			_head->_prev = newNode;*/

			insert(end(), x);
		}

		iterator insert(iterator pos, const T& x)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newNode = new Node(x);

			newNode->_prev = prev;
			prev->_next = newNode;
			newNode->_next = cur;
			cur->_prev = newNode;

			return iterator(newNode);
		}

		void pop_back()
		{
			earse(--end());
		}

		void pop_front()
		{
			earse(begin());
		}

		iterator earse(iterator pos)
		{
			assert(pos != end());

			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;

			delete[] pos._node;

			prev->_next = next;
			next->_prev = prev;

			return iterator(next);
		}

	private:
		Node* _head;
	};
}