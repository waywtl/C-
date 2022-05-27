#define _CRT_SECURE_NO_WARNINGS 1

#pragma once

#include "RBTree.h"

namespace ljh
{
	template<class K, class V>
	class map
	{
	public:
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
		typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}

		iterator find(const K& key)
		{
			return _t.Find(key);
		}

		V& operator[](const K& key)
		{
			auto ret = _t.Insert(make_pair(key, V()));
			return ret.first->second;
		}
	private:
		RBTree<K, pair<K, V>, MapKeyOfT> _t;
	};
}