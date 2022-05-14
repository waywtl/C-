#define _CRT_SECURE_NO_WARNINGS 1

#pragma once 

template<class K>
struct BSTreeNode
{
	BSTreeNode<K>* left;
	BSTreeNode<K>* right;
	K _key;

	BSTreeNode(int key = 0)
		:left(nullptr)
		,right(nullptr)
		,_key(key)
	{}
};

template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	BSTree()
		:_root(nullptr)
	{}

	void InOrder()
	{
		_Inorder(_root);
		cout << endl;
	}

	/*Node* Find(cosnt K& key)
	{
		if (_root == nullptr)
			return nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
				cur = cur->right;
			else if (key < cur->_key)
				cur = cur->left;
			else
				return cur;
		}
		return nullptr;
	}*/

	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			parent = cur;
			if (key > cur->_key)
				cur = cur->right;
			else if (key < cur->_key)
				cur = cur->left;
			else
				return false;
		}
		cur = new Node(key);
		if (key > parent->_key)
			parent->right = cur;
		else
			parent->left = cur;
		return true;
	}

	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}

	bool Erase(const K& key)
	{
		if (_root == nullptr)
		{
			return false;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->left;
			}
			else
			{
				if (cur->left == nullptr)
				{
					if (parent == nullptr)
						_root = cur->right;
					else
					{
						if (cur == parent->left)
							parent->left = cur->right;
						else
							parent->right = cur->right;
					}
				}
				else if (cur->right == nullptr)
				{
					if (parent == nullptr)
						_root = cur->left;
					else
					{
						if (cur == parent->left)
							parent->left = cur->left;
						else
							parent->right = cur->left;
					}
				}
				else
				{
					Node* minParent = cur;
					Node* rightMin = cur->right;
					while (rightMin->left)
					{
						minParent = rightMin;
						rightMin = rightMin->left;
					}
					cur->_key = rightMin->_key;
					if (minParent->left == rightMin)
						minParent->left = rightMin->right;
					else
						minParent->right = rightMin->right;

					cur = rightMin;
				}

				delete cur;
				return true;
			}
		}
		return false;
	}

	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}
private:
	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;
		_Inorder(root->left);
		cout << root->_key << ' ';
		_Inorder(root->right);
	}

	bool _InsertR(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			root = new Node(key);
			return true;
		}
		else
		{
			if (key > root->_key)
				return _InsertR(root->right, key);
			else if (key < root->_key)
				return _InsertR(root->left, key);
			else
				return false;
		}
	}

	bool _EraseR(Node*& root, const K& key)
	{
		if (_root == nullptr)
		{
			return false;
		}

		if (key > root->_key)
			return _EraseR(root->right, key);
		else if (key < root->_key)
			return _EraseR(root->left, key);
		else
		{
			Node* del = root;
			if (root->left == nullptr)
				root = root->right;
			else if (root->right == nullptr)
				root = root->left;
			else
			{
				Node* rightMin = root->right;
				while (rightMin->left)
				{
					rightMin = rightMin->left;
				}
				swap(root->_key, rightMin->_key);
				return _EraseR(root->right, key);
			}
			delete del;
			return true;
		}
	}
private:
	Node* _root;
};