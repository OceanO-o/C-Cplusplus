#pragma once

#pragma warning(disable:4018)

#include <vector>
#include<iostream>
using namespace std;


//·Âº¯Êý                                      ///////////////////////
template <class T>                            ////////////////////////
struct Less                                    ////////////////////////
{
	bool operator()(const T& a, const T& b)const
	{
		return a < b;
	}
};

template <class T>
struct Greater
{
	bool operator()(const T& a, const T& b)const
	{
		return a > b;
	}
};
         //Node* £¬         NodeCompress<T>
template <class T,class compare = NodeCompress<T>>
class MinHeap
{
public:
	MinHeap()
		:_array(NULL)
	{}
	// ×îÐ¡¶Ñ
	MinHeap(const vector<T>& array)
	{
		for (size_t i = 0; i < array.size(); ++i)
		{
			_array.push_back(array[i]);
		}
		moveUp(_array);
	}
	void Display()
	{
		for (size_t i = 0; i < _array.size(); ++i)
		{
			cout << _array[i] << " ";
		}
		cout << endl;
	}
	void Push(const T& x)
	{
		_array.push_back(x);
		moveUp(_array);
	}

	void Pop()
	{
		if (!_array.empty())
		{
			swap(_array[0], _array[_array.size() - 1]);
			_array.pop_back();
			moveDown(0);
		}
	}

	T& Top()
	{
		if (_array[0])
		{
			return _array[0];
		}
	}

	size_t Size()
	{
		return _array.size();
	}

	~MinHeap()
	{}
public:
	bool IsEmpty()const
	{
		if (_array.empty())
		{
			return true;
		}
	}
	void moveUp(vector<T>& array)
	{
		int child = array.size() - 1;
		int parent = (child-1) / 2;
		while (child > 0)
		{
			if (child + 1 < array.size() && (compare()(array[child+1] , array[child])))
			{
				++child;
			}
			if (compare()(array[child] , array[parent]))
			{
				swap(array[parent], array[child]);
				moveDown(child);
			}
			--parent;
			child = parent*2 + 1;
		}
	}
	void moveDown(int parent)
	{
		int child = (parent) * 2 + 1;
		while (child < _array.size())
		{
			if (child + 1 < _array.size() && compare()(_array[child + 1] , _array[child]))
			{
				++child;
			}
			if (compare()(_array[child] , _array[parent]))
			{
				swap(_array[parent], _array[child]);
				parent = child;
				child = child * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
private:
	vector<T> _array;
};

void testheap()
{
	vector<int> arr = { 10, 16, 18, 12, 9, 13, 15, 17, 14, 11 };
	MinHeap<int,Less<int>> heap(arr);
	heap.Display();

	heap.Push(2);
	heap.Display();

	heap.Pop();
	heap.Display();
}

