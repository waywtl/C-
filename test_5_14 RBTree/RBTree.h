#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include <iostream>
using namespace std;

enum Colour{RED, BLACK};

template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	pair<K, V> _kv;

	Colour _col;

	RBTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
		,_col(RED)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(nullptr)
	{}
private:
	//�ҵ���
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
	}

	//����
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
	}

	void RotateLR(Node* parent)
	{
		RotateL(parent->_left);
		RotateR(parent);
	}

	void RotateRL(Node* parent)
	{
		RotateR(parent->_right);
		RotateL(parent);
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	bool _IsBalance(Node* root, int banchmark, int blackNum)
	{
		if (root == nullptr)
		{
			if (blackNum != banchmark)
				return false;
			return true;
		}
		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "����������ɫ�ڵ�" << endl;
			return false;
		}

		if (root->_col == BLACK)
			++blackNum;

		return _IsBalance(root->_left, banchmark, blackNum) 
			&& _IsBalance(root->_right, banchmark, blackNum);
	}
public:
	void InOrder()
	{
		_InOrder(_root);
	}
	bool IsBalance()
	{
		if (_root == nullptr)
			return true;
		if (_root->_col != BLACK)
		{
			cout << "���ڵ㲻�Ǻ�ɫ" << endl;
			return false;
		}

		int banchmark = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
				++banchmark;

			cur = cur->_left;
		}
		int blackNum = 0;
		return _IsBalance(_root, banchmark, blackNum);
	}
	bool Insert(const pair<K, V>& kv)
	{
		//����ڵ�
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
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

		//����ƽ��
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			//�����������游����
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//1.���������Ϊ��
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				//2.���岻����/������Ϊ��
				else
				{
					//curΪ��
					//�ҵ���
					if (cur == parent->_left)
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					//curΪ��
					//����˫��
					else
					{
						RotateLR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//curΪ��
					//����
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					//curΪ��
					//����˫��
					else
					{
						RotateRL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
				}
			}
		}

		_root->_col = BLACK;
		return true;
	}
private:
	Node* _root;
};