#define _CRT_SECURE_NO_WARNINGS 1
#include "AVLTree.h"

void TestAVLTree()
{
	AVLTree<int, int> mytree;
	int a[] = { 4,2,6,1,3,5,15,7,16,14};
	for (auto e : a)
		mytree.Insert(make_pair(e, e));
	mytree.InOrder();
	cout << mytree.IsBalance() << endl;
}

int main()
{
	TestAVLTree();
	return 0;
}