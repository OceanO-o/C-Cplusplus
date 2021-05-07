#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class T>
struct Grater
{
	bool operator()(const T& l, const T& r)
	{
		return l > r;
	}
};
template<class T>
struct Less
{
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};

template <class T,class Compare = Less<T>>
class Heap
{
public:
	Heap()
	{}
	Heap(T* a, int size)
	{
		for (int i = 0; i < size; i++)
		{
			_array.push_back(a[i]);
		}
		for (int i = (_array.size() / 2 - 2); i >= 0; i--)
		{
			AdjustDown(i);
		}
	}

	void AdjustDown(int i)
	{//建立大堆，调整时将，大的调上去，小的调下去，保证每个父节点都比儿子节点大就行了。
		int parent = i;//就一点-->保证下面是小的，把小的往下调。
		int child = parent * 2 + 1;
		Compare com;
		while (com(child, _array.size()))
		{
			if (com(child + 1, _array.size()) && com(_array[child], _array[child + 1]))
			{
				child++;
			}
			if (com(_array[parent], _array[child]))
			{
				swap(_array[child], _array[parent]);
				parent = child;//把小的换到儿子节点，然后如果再小就还是继续往下换。
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}

	void PushBack(const T& x)
	{
		_array.push_back(x);
		_array.pop_back();
		AdjustUp(_array.size() - 1);
	}
	void AdjustUp(int child)
	{//保证一点，把大的往上调（这个都是为大顶堆服务的，这里不考虑排序。）
		int parent = (child - 1) / 2;

		while (child > 0)
		{
			if (_array[child] > _array[parent])
			{
				swap(_array[child], _array[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}

	void PopFront()
	{
		swap(_array[0], _array[_array.size() - 1]);
		AdjustDown(0);
	}
	void Show()
	{
		for (size_t i = 0; i < _array.size(); i++)
		{
			cout << _array[i] << " ";
		}
		cout << endl;
	}
private:
	vector<T> _array;
};

void Test()
{
	int a[10] = { 10, 16, 18, 12, 11, 13, 19, 17, 14, 15 };
	Heap<int,Less<int>> h1(a, sizeof(a)/sizeof(a[0]));

	h1.Show();

	h1.PushBack(20);

	h1.Show();
	h1.PopFront();
	h1.Show();
}

