#define _CRT_SECURE_NO_WARNINGS 1

#pragma once
#include <iostream>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
		,_bf(0)
	{}

	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	int _bf;
	pair<K, V> _kv;
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(nullptr)
	{}
private:
	//右单旋
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		Node* parentP = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parent == parentP->_left)
				parentP->_left = subL;
			else
				parentP->_right = subL;

			subL->_parent = parentP;
		}
		subL->_bf = parent->_bf = 0;
	}

	//左单旋
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		Node* parentP = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parent == parentP->_left)
				parentP->_left = subR;
			else
				parentP->_right = subR;

			subR->_parent = parentP;
		}
		subR->_bf = parent->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == 1)
			subL->_bf = -1;
		else if (bf == -1)
			parent->_bf = 1;
	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		int bf = subRL->_bf;

		RotateR(subR);
		RotateL(parent);

		if (bf == 1)
			parent->_bf = -1;
		else if (bf == -1)
			subR->_bf = 1;
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_kv.first << ':' << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	int Hight(Node* root)
	{
		if (root == nullptr)
			return 0;
		return 1 + max(Hight(root->_left), Hight(root->_right));
	}
	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;
		int leftHight = Hight(root->_left);
		int rightHight = Hight(root->_right);

		int diff = rightHight - leftHight;
		if (diff != root->_bf)
		{
			cout << root->_kv.first << "现在是:" << root->_bf << endl;
			cout << root->_kv.first << "应该是:" << diff << endl;
			return false;
		}

		return abs(diff) <= 1 && _IsBalance(root->_left) && _IsBalance(root->_right);
	}
public:
	void InOrder()
	{
		_InOrder(_root);
	}
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
	bool Insert(const pair<K, V>& kv)
	{
		//插入节点
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			parent = cur;
			if (kv.first > cur->_kv.first)
				cur = cur->_right;
			else if (kv.first < cur->_kv.first)
				cur = cur->_left;
			else
				return false;
		}
		cur = new Node(kv);
		if (kv > parent->_kv)
			parent->_right = cur;
		else
			parent->_left = cur;
		cur->_parent = parent;
	
		//控制平衡
		while (parent)
		{
			if (cur == parent->_left)
				--parent->_bf;
			else
				++parent->_bf;

			//插入后使父节点平衡
			if (parent->_bf == 0)
				break;

			//插入后使父节点不平衡，但仍满足AVLTree的条件，但此时需要往上更新
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_parent;
			}

			//不满足AVLTree的条件，需要旋转
			else
			{
				//旋转
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					//左单旋
					RotateL(parent);
				}
				else if(parent->_bf == -2 && cur->_bf == -1)
				{
					//右单旋
					RotateR(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					//左右双旋
					RotateLR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					//右左双旋
					RotateRL(parent);
				}
				break;
			}
		}
		return true;
	}
private:
	Node* _root;
};