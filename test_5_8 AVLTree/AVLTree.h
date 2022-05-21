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
		subL->_bf = parent->_bf = 0;
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
			cout << root->_kv.first << "������:" << root->_bf << endl;
			cout << root->_kv.first << "Ӧ����:" << diff << endl;
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
		//����ڵ�
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
	
		//����ƽ��
		while (parent)
		{
			if (cur == parent->_left)
				--parent->_bf;
			else
				++parent->_bf;

			//�����ʹ���ڵ�ƽ��
			if (parent->_bf == 0)
				break;

			//�����ʹ���ڵ㲻ƽ�⣬��������AVLTree������������ʱ��Ҫ���ϸ���
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_parent;
			}

			//������AVLTree����������Ҫ��ת
			else
			{
				//��ת
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					//����
					RotateL(parent);
				}
				else if(parent->_bf == -2 && cur->_bf == -1)
				{
					//�ҵ���
					RotateR(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					//����˫��
					RotateLR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					//����˫��
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