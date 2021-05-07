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
	{//������ѣ�����ʱ������ĵ���ȥ��С�ĵ���ȥ����֤ÿ�����ڵ㶼�ȶ��ӽڵ������ˡ�
		int parent = i;//��һ��-->��֤������С�ģ���С�����µ���
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
				parent = child;//��С�Ļ������ӽڵ㣬Ȼ�������С�ͻ��Ǽ������»���
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
	{//��֤һ�㣬�Ѵ�����ϵ����������Ϊ�󶥶ѷ���ģ����ﲻ�������򡣣�
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

