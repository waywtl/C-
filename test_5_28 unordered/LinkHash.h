#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace LinkHash
{
	template<class K>
	struct Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<>
	struct Hash<string>
	{
		size_t operator()(const string& s)
		{
			size_t val = 0;
			for (auto ch : s)
			{
				val *= 31;
				val += ch;
			}
			return val;
		}
	};

	template<class T>
	struct HashNode
	{
		HashNode<T>* _next;
		T _data;

		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};

	template<class K, class T, class KeyOfT, class HashFunc>
	class HashTable;

	template<class K, class T, class Ptr, class Ref, class KeyOfT, class HashFunc>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef __HTIterator<K, T, Ptr, Ref, KeyOfT, HashFunc> Self;

		Node* _node;
		HashTable<K, T, KeyOfT, HashFunc>* _pht;

		__HTIterator(Node* node, HashTable<K, T, KeyOfT, HashFunc>* pht)
			:_node(node)
			,_pht(pht)
		{}

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		Self& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				KeyOfT kot;
				HashFunc hf;
				size_t index = hf(kot(_node->_data)) % _pht->_tables.size();
				++index;
				//找下一个不为空的桶
				while (index < _pht->_tables.size())
				{
					if (_pht->_tables[index])
					{
						break;
					}
					else
					{
						++index;
					}
				}
				if (index == _pht->_tables.size())
				{
					_node = nullptr;
				}
				else
				{
					_node = _pht->_tables[index];
				}
			}
			return *this;
		}

		bool operator!=(const Self& s) const
		{
			return _node != s._node;
		}

		bool operator==(const Self& s) const
		{
			return _node == s._node;
		}
	};

	template<class K, class T, class KeyOfT, class HashFunc>
	class HashTable
	{
		typedef HashNode<T> Node;
		typedef HashTable<K, T, KeyOfT, HashFunc> Self;
		template<class K, class T, class Ptr, class Ref, class KeyOfT, class HashFunc>
		friend struct __HTIterator;
	public:
		typedef __HTIterator<K, T, T*, T&, KeyOfT, HashFunc> iterator;

		/*HashTable()
		{}*/

		HashTable() = default;

		HashTable(const Self& ht)
		{
			_tables.resize(ht._tables.size());
			for (size_t i = 0; i < ht._tables.size(); ++i)
			{
				Node* cur = ht._tables[i];
				while (cur)
				{
					Node* copy = new Node(cur->_data);
					copy->_next = _tables[i];
					_tables[i] = copy;
					cur = cur->_next;
				}
			}
		}

		Self& operator=(Self ht)
		{
			swap(_size, ht._size);
			_tables.swap(ht._tables);
			return *this;
		}

		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}
	public:
		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i])
				{
					return iterator(_tables[i], this);
				}
			}
			return end();
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		iterator Find(const K& key)
		{
			if (_tables.empty())
				return end();

			HashFunc hf;
			size_t index = hf(key) % _tables.size();
			Node* cur = _tables[index];
			KeyOfT kot;
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return iterator(cur, this);
				}
				else
				{
					cur = cur->_next;
				}
			}
			return end();
		}

		bool Erase(const K& key)
		{
			if (_tables.empty())
				return false;

			HashFunc hf;
			size_t index = hf(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[index];
			KeyOfT kot;
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					//头删
					if (prev == nullptr)
						_tables[index] = cur->_next;
					//中间删除
					else
						prev->_next = cur->_next;

					--_size;
					delete cur;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}

		size_t GetNextPrime(size_t num)
		{
			const size_t prime_list[30] =
			{
				13,         29,         53,         97,         193,       
				389,        769,        1543,       3079,       6151,
				12289,      24593,      49157,      98317,      196613,
				393241,     786433,     1572869,    3145739,    6291469,
				12582917,   25165843,   50331653,   100663319,  201326611,
				402653189,  805306457,  1610612741, 3221225473, 4294967291
			};

			for (size_t i = 0; i < 30; ++i)
			{
				if (prime_list[i] > num)
				{
					return prime_list[i];
				}
			}
			return prime_list[29];
		}

		pair<iterator, bool> Insert(const T& data)
		{
			KeyOfT kot;
			iterator ret = Find(kot(data));
			if (ret != end())
				return make_pair(ret, false);

			HashFunc hf;
			//扩容
			if (_size == _tables.size())
			{
				size_t newSize = GetNextPrime(_tables.size());

				vector<Node*> newTables;
				newTables.resize(newSize);
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						size_t index = hf(kot(cur->_data)) % newTables.size();
						
						//头插
						cur->_next = newTables[index];
						newTables[index] = cur;

						cur = next;
					}
				}
				_tables.swap(newTables);
			}

			size_t index = hf(kot(data)) % _tables.size();
			Node* newnode = new Node(data);
			//头插
			newnode->_next = _tables[index];
			_tables[index] = newnode;

			++_size;
			return make_pair(iterator(newnode, this), true);
		}
	private:
		vector<Node*> _tables;
		size_t _size = 0;
	};
}