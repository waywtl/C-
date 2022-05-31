#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include "LinkHash.h"
using namespace LinkHash;

namespace ljh_unordered_map
{
	template<class K, class V, class hash = Hash<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename LinkHash::HashTable<K, pair<K, V>, MapKeyOfT, hash>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		V& operator[](const K& key)
		{
			auto ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}

		iterator find(const K& key)
		{
			return _ht.Find(key);
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}

		bool erase(const K& key)
		{
			return _ht.Erase(key);
		}

	private:
		LinkHash::HashTable<K, pair<K, V>, MapKeyOfT, hash> _ht;
	};
}