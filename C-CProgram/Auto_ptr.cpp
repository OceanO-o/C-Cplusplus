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
	AutoPtr(AutoPtr<T>& s)     //���治����const����Ϊ����Ҫ���������ı����ֵ
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
	AutoPtr<int> p1 = new int(10);//������ô�ܸ�ֵ�ɹ��أ� ����������ǿ������ת��
	                             // new int -> Autoptr<int>(�������ָ��) Ȼ�󿽱������p1
	AutoPtr<int> p2 = new int;
	*p2 = 20;

	AutoPtr<AA> p3 = new AA;   //p3������һ��ָ�룬��ʼ��ΪAA ���͵�ָ�� ����˸�ָ�뺬��_a
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
class ScopePtr        //������
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
	ScopePtr<int> p3 = p1;//������ʱ������ֱ�ӱ���---> ����
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







