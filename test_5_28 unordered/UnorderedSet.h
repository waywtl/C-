#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include "LinkHash.h"
using namespace LinkHash;

namespace ljh_unordered_set
{
	template<class K, class hash = Hash<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename LinkHash::HashTable<K, K, SetKeyOfT, hash>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		iterator find(const K& key)
		{
			return _ht.Find(key);
		}

		pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
		}
		
		bool erase(const K& key)
		{
			return _ht.Erase(key);
		}

	private:
		LinkHash::HashTable<K, K, SetKeyOfT, hash> _ht;
	};
}