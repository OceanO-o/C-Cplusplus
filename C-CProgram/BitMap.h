#pragma once
#include<iostream>
#include<vector>
using namespace std;

class BitMap
{
public:
	BitMap()
		:_size(0)
	{}

	BitMap(size_t size)
		:_size(0)
	{
		_arrays.resize((size >> 5) + 1);
	}

	bool Set(size_t num)//把存在的数的位置1
	{
		size_t index = num >> 5;
		size_t n = num % 32;

		if (_arrays[index] & (1 << n))//如果存在就不用再置1了
		{
			return false;
		}
		_arrays[index] |= (1 << n);
		++_size;
		return true;
	}
	bool ReSet(size_t num)
	{
		size_t index = num >> 5;
		size_t n = num % 32;

		if (_arrays[index] & (1 << n))
			//    ~(1<<n)
		{
			_arrays[index] &= (~(1 << n));
			--_size;
			return true;
		}
		return false;
	}
	bool Test(size_t num)
	{
		size_t index = num >> 5;
		size_t n = num % 32;

		return _arrays[index] & (1 << n);
	}
	void Clear()
	{
		_arrays.assign(_arrays.size(), 0);
	}
private:
	vector<size_t> _arrays;
	size_t _size;
};

void Test1()
{
	BitMap bm(65);
	bm.Set(1);
	bm.Set(4);
	bm.Set(33);
	
	cout << "1?" << bm.Test(1) << endl;
	cout << "2?" << bm.Test(2) << endl;
	cout << "4?" << bm.Test(4) << endl;
	cout << "33?" << bm.Test(33) << endl;

	bm.ReSet(1);
	bm.ReSet(33);

	cout << "1?" << bm.Test(1) << endl;
	cout << "4?" << bm.Test(4) << endl;
	cout << "33?" << bm.Test(33) << endl;
}
void Test2()
{
	BitMap bm(-1);
	bm.Set(10000000000);
}