#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#include "BSTree.h"

void TestBSTree()
{
	BSTree<int> t;
	int a[] = {5,4,3,0,1,8,7,9,2,6};
	for (auto e : a)
	{
		t.InsertR(e);
	}
	t.InOrder();

	t.EraseR(4);
	t.InOrder();

	t.EraseR(7);
	t.InOrder();
}

int main()
{
	TestBSTree();
	return 0;
}