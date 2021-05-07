#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

template <class T>
class Stack
{
public:
	Stack()
		:_array(NULL)
		, _size(0)
		, _capacity(0)
	{}
	~Stack()
	{
		if (_array)
		{
			delete[]_array;
		}
	}

	void Push(const T& x)
	{
		_Checkcapacity();
		_array[_size++] = x;
	}

	void Pop()
	{
		assert(_size);
		_size--;
	}

	size_t Size()
	{
		return _size;
	}

	void Empty()
	{
		_size = 0;
	}

	T& Top()
	{
		return _array[_size - 1];
	}

	void Show()
	{
		cout << "Õ»¶¥->";
		for (int i = _size - 1; i >= 0; i--)
		{
			cout << _array[i] << "->";
		}
		cout << "Õ»µ×" << endl;
	}
private:
	void _Checkcapacity()
	{
		if (_size >= _capacity)
		{
			_capacity = _capacity * 2 + 3;
			T* tmp = new T[_capacity];
			for (size_t i = 0; i < _size; i++)
			{
				tmp[i] = _array[i];
			}

			delete[]_array;
			_array = tmp;
		}
	}
private:
	T* _array;
	size_t _size;
	size_t _capacity;
};

void Test()
{
	Stack<int> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Push(5);
	s1.Push(6);
	s1.Push(7);

	s1.Show();

	s1.Pop();
	s1.Pop();
	s1.Show();

	s1.Empty();
	s1.Show();

}