#pragma once
#include<iostream>
                                            //C++实现顺序表
using namespace std;
typedef int DateType;
class SeqList
{
public:
	
	SeqList()
		:_array(NULL)
		, _size(0)
		, _capacity(0)
	{}

	SeqList(DateType* array, size_t size, size_t capacity)
		:_array(new DateType[size])
		, _size(size)
		, _capacity(capacity)
	{
		memcpy(_array, array,sizeof(DateType)*size);
	}

	SeqList(const SeqList& s)
	{
		_array = new DateType[s._capacity];
		memcpy(_array, s._array, sizeof(DateType)*s._size);
		_size = s._size;
		_capacity = s._capacity;
	}

	SeqList& operator=(const SeqList& s)
	{
		if (this != &s)
		{
			delete[] _array;//考虑的是自己已经有值，
			_array = new DateType[s._capacity];
			memcpy(_array, s._array, sizeof(DateType)*s._size);
			_size = s._size;
			_capacity = s._capacity;
		}
		return *this;
	}

	~SeqList()
	{
		if (_array)
		{
			delete[] _array;
			//_array = NULL;
		}
	}
	void Print()
	{
		for (size_t i = 0; i < _size; i++)
		{
			cout << _array[i] << " ";
		}
		cout << endl;
	}

	//一般不写PushFront()因为每次要移动，如果数据很大，则浪费时间
	void PushBack(const DateType& x)
	{
		_CheckCapacity();
		_array[_size] = x;
		_size++;
	}

	bool PopBack()
	{
		//_size = 0? 空表？
		if (_size == 0)
		{
			cout << "empty SeqList" << endl;
			return 0;
		}
		--_size;
		
		return 1;
	}

	bool Insert(size_t pos, const DateType& x)//往后面插入
	{
		if (pos > _size)
		{
			cout << "Insert encounter an sorrow" << endl;
			return 0;
		}

		_CheckCapacity();
		for (size_t i = _size; i >= pos; i--)
		{
			_array[i+1] = _array[i];
		}
		_array[pos] = x;
		_size++;

		return 1;
	}

	bool Find(const DateType& x)
	{
		for (size_t i = 0; i < _size; i++)
		{
			if (_array[i] == x)
			{
				cout << "find success" << endl;
				return 1;
			}
		}
		cout << "no find" << endl;
		return 0;
	}

	bool Erase(size_t pos)
	{
		if (pos <= 0 || pos > _size)
		{
			cout << "please input correct pos" << endl;
			return 0;
		}
		if (pos == _size)
		{
			PopBack();
			return 1;
		}
		for (size_t i = pos-1; i < _size; i++)
		{
			_array[i] = _array[i + 1];
		}
		_size--;
		return 1;
	}
	int Size()
	{
		return _size;
	}

	int Capacity()
	{
		return _capacity;
	}
	void clear()
	{
		_size = 0;
	}

private:
	void _CheckCapacity()
	{
		if (_size >= _capacity)
		{
			_capacity = _capacity * 2 + 3;
			DateType* tmp = new DateType[_capacity];
			memcpy(tmp, _array, sizeof(DateType)*_size);
			delete[] _array;
			_array = tmp;
		}

	}
private:
	DateType* _array;
	size_t    _size;
	size_t    _capacity;
};

void Test()
{
	int a[5] = { 1, 2, 3, 4, 5 };
	int b[5] = { 5, 4, 3, 2, 1 };
	SeqList s1(a, sizeof(a) / sizeof(a[0]),sizeof(a)/sizeof(a[0]));

	s1.PushBack(6);
	s1.PushBack(7);
	s1.Print();

	//s1.PushBack(7);
	//s1.PushBack(7);

	//s1.PushBack(7);
	//s1.PushBack(7);
	//s1.PushBack(7); 
	//s1.PushBack(7);
	//s1.PushBack(7);
	//s1.PushBack(7);
	//s1.PushBack(7);
	//s1.Print();

	//SeqList s2(s1);  //测试拷贝构造

	//SeqList s3(b, sizeof(b) / sizeof(b[0]), sizeof(b) / sizeof(b[0]));
	//s3 = s2;      //测试赋值运算符重载

	/*s1.PopBack(); //测试空表弹出怎么办
	s1.PopBack();
	s1.PopBack();
	s1.PopBack();
	s1.PopBack();
	s1.PopBack();
	s1.PopBack();
	s1.PopBack();
	s1.PopBack();
	s1.Print();*/
	
	//s1.Insert(1, 4);

	//s1.Insert(1, 4);
	//s1.Insert(1, 4);
	//s1.Insert(1, 4);
	//s1.Insert(1, 4);
	//s1.Insert(1, 4);
	//s1.Insert(1, 5);



	s1.Print();

	s1.Find(2);
	s1.Erase(7);
	s1.Print();
}
int main()
{
	Test();
	system("pause");
	return 0;
}