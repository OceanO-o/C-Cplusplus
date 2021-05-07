#pragma once
#include<iostream>
using namespace std;
#include<queue>
template <class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	BinaryTreeNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template <class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(T* a, size_t size)
	{
		size_t index = 0;
		_root = _CreateTree(a, size, index);
	}

	~BinaryTree()
	{
		_Destroy(_root);
		_root = NULL;
	}

	BinaryTree(const BinaryTree<T>& b)
	{
		_root = _Copy(b._root);
		
	}

	BinaryTree<T>& operator=(BinaryTree<T> b)
	{
		swap(_root, b._root);
		return *this;
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}

	void LevelOrder()
	{
		if (_root != NULL)
		{
			queue<BinaryTreeNode<int>*> q1;
			q1.push(_root);
			while (!q1.empty())
			{
				BinaryTreeNode<int>* front =q1.front();
				cout << front->_data<<" ";
				q1.pop();//其实是front，但是保存起来了。

				if (front->_left)
				{
					q1.push(front->_left);
				}
				if (front->_right)
				{
					q1.push(front->_right);
				}
			}
			cout << endl;
		}
	}

	int Size()
	{
		int size = 0;
		_Size(_root, size);
		return size;
	}

	int Depth()
	{
		int depth = 0;
		depth = _Depth(_root);
		return depth;
	}
protected:
	BinaryTreeNode<T>* _CreateTree(T* a, size_t size, size_t& index)
	{
		BinaryTreeNode<T>* root = NULL;
		if (index < size && (a[index] != '#'))
		{
			root = new BinaryTreeNode<T>(a[index]);
			root->_left = _CreateTree(a,size,++index);
			root->_right = _CreateTree(a, size, ++index);
		}
		return root;
	}

	void _Destroy(BinaryTreeNode<T>* &root)
	{
		if (root == NULL)
			return;
		if (root->_left == NULL && root->_right == NULL)
		{
			delete root;
			root = NULL;
			return;
		}
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	BinaryTreeNode<T>* _Copy(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return NULL;
		BinaryTreeNode<T>* newRoot = new BinaryTreeNode<T>(root->_data);
		newRoot->_left = _Copy(root->_left);
		newRoot->_right = _Copy(root->_right);

		return newRoot;

	}

	void _PrevOrder(BinaryTreeNode<T> *root)
	{
		if (root != NULL)
		{
            _PrevOrder(root->_left);
			cout << root->_data << " ";
			_PrevOrder(root->_right);
		}
	}

	void _InOrder(BinaryTreeNode<T> *root)
	{
		if (root != NULL)
		{
			cout << root->_data << " ";
			_InOrder(root->_left);
			_InOrder(root->_right);
		}
	}

	void _PostOrder(BinaryTreeNode<T>* root)
	{
		if (root != NULL)
		{
			_PostOrder(root->_left);
			_PostOrder(root->_right);
			cout << root->_data<<" ";
		}
	}

	void _Size(BinaryTreeNode<T>* root, int& size)
	{
		if (root == NULL)
			return;
		else
			++size;

		_Size(root->_left,size);
		_Size(root->_right,size);
	}

	int _Depth(BinaryTreeNode<T>* root)
	{
		int leftdepth = _Depth(root->_left);
		int rightdepth = _Depth(root->_right);
		return leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;
	}
private:
	BinaryTreeNode<T>* _root;
};

void Test()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> b1(a, sizeof(a) / sizeof(a[0]));
	BinaryTree<int> b2(b1);

	/*int b[10] = { 1, 6, 3, '#', '#', 4, '#', '#', 5, 2};
	BinaryTree<int> b3(b, sizeof(b) / sizeof(b[0]));

	b3 = b2;*/

	b2.PrevOrder();
	b2.InOrder();
	b2.PostOrder();

	b2.LevelOrder();

	int size = b2.Size();
	cout << "size = " << size << endl;
	int depth = b2.Depth();
	cout << "depth = " << depth << endl;
}