#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include <iostream>
using namespace std;

enum Colour{RED, BLACK};

template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	T _data;

	Colour _col;

	RBTreeNode(const T& data)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_data(data)
		,_col(RED)
	{}
};

template<class T, class Ref, class Ptr>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T, Ref, Ptr> self;
public:
	RBTreeIterator(Node* node = nullptr)
		:_node(node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	self& operator++()
	{
		Increament();
		return *this;
	}

	self operator++(int)
	{
		Node* tmp = _node;
		Increament();
		return tmp;
	}

	self& operator--()
	{
		Deincreament();
		return *this;
	}

	self operator--(int)
	{
		Node* tmp = _node;
		Deincreament();
		return tmp;
	}

	bool operator!=(const self& s) const
	{
		return _node != s._node;
	}

	bool operator==(const self& s) const
	{
		return _node == s._node;
	}
private:
	void Increament()
	{
		if (_node->_right)
		{
			Node* cur = _node->_right;
			while (cur && cur->_left)
			{
				cur = cur->_left;
			}
			_node = cur;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
	}
	void Deincreament()
	{
		if (_node->_left)
		{
			Node* cur = _node->_left;
			while (cur && cur->_right)
			{
				cur = cur->_right;
			}
			_node = cur;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
	}
private:
	Node* _node;
};

template<class K, class T, class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef RBTreeIterator<T, T&, T*> iterator;
	typedef RBTreeIterator<const T, const T&, const T*> const_iterator;

	RBTree()
		:_root(nullptr)
	{}
		
	RBTree(const RBTree<K, T, KeyOfT>& t)
	{
		_root = Copy(t._root);
	}

	RBTree<K, T, KeyOfT>& operator=(RBTree<K, T, KeyOfT> t)
	{
		std::swap(_root, t._root);
		return *this;
	}

	~RBTree()
	{
		Destroy(_root);
	}

	iterator begin()
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return iterator(cur);
	}

	iterator end()
	{
		return iterator(nullptr);
	}
public:
	iterator Find(const K& key)
	{
		Node* cur = _root;
		KeyOfT kot;
		while (cur)
		{
			if(key > kot(cur->_data))
				cur = cur->_right;
			else if(key < kot(cur->_data))
				cur = cur->_left;
			else
				return iterator(cur);
		}
	}

	pair<iterator, bool> Insert(const T& data)
	{
		//²åÈë½Úµã
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(iterator(_root), true);
		}

		KeyOfT kot;

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			parent = cur;
			if (kot(data) > kot(cur->_data))
				cur = cur->_right;
			else if (kot(data) < kot(cur->_data))
				cur = cur->_left;
			else
				return make_pair(iterator(cur), false);
		}
		cur = new Node(data);
		Node* newNode = cur;
		if (kot(data) > kot(parent->_data))
			parent->_right = cur;
		else
			parent->_left = cur;
		cur->_parent = parent;

		//¿ØÖÆÆ½ºâ
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			//¸¸´æÔÚÇÒÔÚ×æ¸¸µÄ×ó
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//1.ÊåÊå´æÔÚÇÒÎªºì
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				//2.ÊåÊå²»´æÔÚ/´æÔÚÇÒÎªºÚ
				else
				{
					//curÎª×ó
					//ÓÒµ¥Ðý
					if (cur == parent->_left)
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					//curÎªÓÒ
					//×óÓÒË«Ðý
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
					//curÎªÓÒ
					//×óµ¥Ðý
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					//curÎª×ó
					//ÓÒ×óË«Ðý
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
		return make_pair(iterator(newNode), true);
	}
private:
	//ÓÒµ¥Ðý
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

	//×óµ¥Ðý
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

	void Destroy(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}

	Node* Copy(Node* root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}

		Node* newRoot = new Node(root->_data);
		newRoot->_col = root->_col;

		newRoot->_left = Copy(root->_left);
		newRoot->_right = Copy(root->_right);

		if (newRoot->_left)
			newRoot->_left->_parent = newRoot;
		if (newRoot->_right)
			newRoot->_right->_parent = newRoot;
		return newRoot;
	}
private:
	Node* _root;
};