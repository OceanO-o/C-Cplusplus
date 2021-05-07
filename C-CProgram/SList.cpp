#pragma once
#include<iostream>
using namespace std;

typedef int DataType;
struct ListNode
{
	ListNode(const DataType& x)
	:_data(x)
	, _next(NULL)
	{}
	DataType _data;
	ListNode* _next;
};

class SList
{
public:
	SList()
	:_head(NULL)
	, _tail(NULL)
	{}

	~SList()
	{
		_Destroy();
	}
	//拷贝构造
	SList(const SList& s)
		:_head(NULL)
		, _tail(NULL)
	{
		if (s._head == NULL)
		{
			return;
		}
		ListNode * begin = s._head;
		while (begin)
		{
			PushBack(begin->_data);
			begin = begin->_next;
		}
	}
	//赋值运算符重载
	SList& operator=(const SList& s)
	{
		if (this != &s)
		{
			_Destroy();
			ListNode* begin = s._head;
			while (begin)
			{
				PushBack(begin->_data);
				begin = begin->_next;
			}
		}
		return *this;
	}
	//尾插
	void PushBack(const DataType& x)
	{
		if (_head == NULL)
		{
			_head = new ListNode(x);
			_tail = _head;
		}
		else
		{
			_tail->_next = new ListNode(x);
			_tail = _tail->_next;
		}
	}
	//尾删
	bool PopBack()
	{
		if (_head == NULL)
		{
			cout << "empty list" << endl;
			return 0;
		}
		//一个节点
		if (_head->_next == NULL)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			ListNode* begin = _head;
			ListNode* cur = NULL;

			while (begin->_next)
			{
				cur = begin;
				begin = begin->_next;
			}			
			cur->_next = NULL;
			delete begin;
			_tail = cur;
		}

	}
	//打印链表
	void Print()
	{
		ListNode* begin = _head;
		while (begin)
		{
			cout << begin->_data << "->";
			begin = begin->_next;
		}
		cout << "NULL" << endl;
	}
	//逆置链表
	void Reverse()
	{
		if (_head == NULL)
		{
			cout << "empty list" << endl;
			return;
		}
		if (_head->_next == NULL)
		{
			cout << "single listnode,no Reverse" << endl;
			return;
		}

		ListNode* newHead = NULL;
		ListNode* begin = _head;
		while (begin)//逆置链表相当于重新建立链表，
		{			
			ListNode* prev = begin;  //开始取节点
			begin = begin->_next;    

			prev->_next = newHead;    //链接
			newHead = prev;			
		}
		_head = newHead;
		_tail = begin;
	}
private:
	void _Destroy()
	{
		ListNode* begin = _head;
		while (begin)
		{
			ListNode* cur = begin;
			begin = begin->_next;
			delete cur;
		}
		_head = NULL;
		_tail = NULL;
	}
private:
	ListNode* _head;
	ListNode* _tail;
};

void Test()
{
	SList s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(5);

	s1.Print();

	////s1.PopBack();
	//

	////s1.Print();

	//SList s2(s1);
	//s2.Print();

	SList s3;
	s3.PushBack(2);
	s3.PushBack(3);
	s3.PushBack(4);

	s1 = s3;
	s3.Print();
	s1.Print();

	s3.Reverse();
	s3.Print();
}
int main()
{
	Test();
	system("pause");
	return 0;
}