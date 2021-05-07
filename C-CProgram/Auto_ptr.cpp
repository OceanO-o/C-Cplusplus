#pragma once
#include<iostream>
using namespace std;

class AA
{
public:
	void Dispaly()
	{
		cout << _a << endl;
	}
private:
	int _a;
};

template<class T>
class AutoPtr
{
public:
	AutoPtr( T* ptr)
		:_ptr(ptr)
	{}
	AutoPtr(AutoPtr<T>& s)     //里面不能用const，因为这里要防拷贝，改变这个值
		:_ptr(s._ptr)
	{
		s._ptr = NULL;
	}

	AutoPtr& operator=(AutoPtr<T>& s)
	{
		if (s._ptr != _ptr)
		{
			delete _ptr;
			_ptr = s._ptr;
			s._ptr = NULL;
		}
		return *this;
	}

	~AutoPtr()
	{
		if (_ptr)
			delete _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}
private:
	T* _ptr;
};

void Test()
{
	AutoPtr<int> p1 = new int(10);//这里怎么能赋值成功呢？ 在这里先是强制类型转换
	                             // new int -> Autoptr<int>(里面就是指针) 然后拷贝构造给p1
	AutoPtr<int> p2 = new int;
	*p2 = 20;

	AutoPtr<AA> p3 = new AA;   //p3里面有一个指针，初始化为AA 类型的指针 ，因此该指针含有_a
	(*p3).Dispaly();           //

	AutoPtr<int> px(p1);  

	AutoPtr<int> ap1 = new int(1);
	AutoPtr<int> ap2(ap1);
	AutoPtr<int> ap3(ap2);
	*ap1 = 10;


	AutoPtr<int> p4 = new int;
	AutoPtr<int> p5 = p4;
}


template<class T>
class ScopePtr        //防拷贝
{
public:
	ScopePtr(T* ptr)
		:_ptr(ptr)
	{}
	~ScopePtr()
	{
		if (_ptr)
			delete _ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}

private:
	ScopePtr(const ScopePtr& sp);

	ScopePtr<T>& operator=(const ScopePtr& sp);
	
private:
	T* _ptr;
};

void Test()
{
	ScopePtr<int> p1 = new int(10);
	ScopePtr<int> p2 (p1);
	ScopePtr<int> p3 = p1;//防拷贝时，调用直接报错，---> 暴力
}

template <class T>
class SharePtr
{
public:
	SharePtr( T* ptr)
		:_ptr(ptr)
		, _pCount(new int(1))
	{}

	~SharePtr()
	{
		if (--(*_pCount) == 0)
		{
			delete _pCount;
			delete _ptr;
		}
	}

	SharePtr(SharePtr<T>& s)
		:_ptr(s._ptr)
		, _pCount(s._pCount)
	{
		++*_pCount;
	}

	SharePtr<T>& operator=(SharePtr<T>& s)
	{
		if (this != &s)
		{
			if ( --(*_pCount) == 0 )
			{
				delete _ptr;
				delete _pCount;
			}

			_ptr = s._ptr;
			_pCount = s._pCount;
			++(*_pCount);

		}
		return *this;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	int *_pCount;
	T    *_ptr;
};

void Test()
{
	SharePtr<int> s1 = new int(10);
	SharePtr<int> s2(s1);
	SharePtr<int> s3 = new int(20);
	s2 = s3;

	*s2 = 100;
}







