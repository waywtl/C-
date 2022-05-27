#define _CRT_SECURE_NO_WARNINGS 1

#include "MyMap.h"
#include "MySet.h"

void TestMap()
{
	ljh::map<string, int> m;
	m.insert(make_pair("aaa", 4));
	m.insert(make_pair("bbb", 8));
	m.insert(make_pair("ccc", 5));
	m.insert(make_pair("ddd", 1));
	m.insert(make_pair("eee", 3));
	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << m["gg"] << endl;
}

void TestSet()
{
	ljh::set<int> s;
	s.insert(2);
	s.insert(8);
	s.insert(3);
	s.insert(4);
	s.insert(7);
	s.insert(1);
	s.insert(14);
	s.insert(16);
	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << endl;
		++it;
	}
	ljh::set<int> cp(s);
	ljh::set<int> ss;
	ss.insert(11);
	ss.insert(22);
	ss.insert(33);

	ss = s;
}

int main()
{
	//TestMap();
	TestSet();
	return 0;
}