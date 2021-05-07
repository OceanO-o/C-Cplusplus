#pragma once
#include<iostream>

using namespace std;
typedef int DataType;
struct ListNode
{
	ListNode(const DataType& x)
	:_data(x)
	, _prev(NULL)
	, _next(NULL)
	{}
	DataType _data;
	ListNode* _prev;
	ListNode* _next;
};

class DoubleList
{
public:

	DoubleList()
	:_head(NULL)
	, _tail(NULL)
	{}

	~DoubleList()
	{
		PopFront();

	}
	DoubleList(const DoubleList& s)
		:_head(NULL)
		, _tail(NULL)
	{
		if (s._head == NULL)
		{
			cout << "empty list , no copy" << endl;
			return;
		}
		else
		{
			ListNode* begin = s._head;
			while (begin != s._tail)  //如果只有一个节点呢？
			{
				PushBack(begin->_data);
				begin = begin->_next;
			}
			PushBack(s._tail->_data);
		}
	}

	DoubleList& operator=(const DoubleList& s)
	{
		if (this != &s)
		{                              
			if (s._head != NULL)
					
			{                     //this对象里面已经存在值，现需要destroy掉。
				//ListNode* begin1 = _head;
				//while (begin1) 这里有bug，死循环，调试可知begin1最终不为null.
				while (_head)  //如果只有一个节点呢？
				{
					
					PopFront();	

				}			
				
				ListNode* begin = s._head;

				while (begin != s._tail)  //如果只有一个节点呢？
				{
					PushBack(begin->_data);
					begin = begin->_next;
				}
				PushBack(s._tail->_data);//只有一个节点那么直接pushback tail->_data,也就是head->data
				return *this;
			}
		}
	}

	void PushBack(const DataType& x)
	{
		//空链表
		if (_head == NULL)
		{
			_head = new ListNode(x);
			_tail = _head;
		}
		//非空链表
		else
		{
			ListNode* ret = new ListNode(x);
			_tail->_next = ret;
			ret->_prev = _tail;
			_tail = ret;
			_tail->_next = _head;
			                        //头的prev
			_head->_prev = _tail;
		}
	}
	void PopFront()
	{
		//空链表
		if (_head == NULL)
		{
			cout << "empty doublelidt" << endl;
			
		}
		//一个节点
		else if (_head == _tail)
		{
			delete _head;
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			/*ListNode* ret = _head;
			ListNode* tmp = ret;
			ret = ret->_next;
			                        //这样做两个节点就出现问题了
			ret->_prev = _tail;
			_tail->_next = ret;

			delete tmp;
			tmp = NULL;*/
			ListNode* ret = _head;
			_head = _head->_next;

			_head->_prev = _tail;
			_tail->_next = _head;

			delete ret;
			ret = NULL;
		}
	}

	void Print()
	{
		ListNode* begin = _head;
		if (_head == NULL)
		{
			cout << "empty list" << endl;
		}
		/*else if (_head == _tail)
		{			
		
			cout << _head->_data << endl;	
			
		}
		else
		{
			while (begin != _tail)
			{
				cout << begin->_data<< "->";
				begin = begin->_next;
			} 
			cout << _tail->_data << "->""NULL" << endl;
		}*/
		else
		{
			ListNode* begin = _head;
			while (begin != _tail)  //如果只有一个节点呢？
			{
				cout << begin->_data << "->";
				begin = begin->_next;
			}
			cout << _tail->_data << "->""NULL" << endl;
		}
	}

	/*void Reverse()
	{
		ListNode* cur = _head;
		while (cur!= _tail)
		{
			swap(cur->_prev, cur->_next);
			cur = cur->_next;
		}
		swap(_tail->_next, _tail->_prev);

		swap(_head, _tail); //bug
	}*/
private:
	ListNode* _head;
	ListNode* _tail;
};

void Test()
{
	DoubleList s;
	s.PushBack(1);
	s.PushBack(2);
	s.PushBack(3);
	s.PushBack(4);
	s.PushBack(5);
	s.Print();

	/*s.PopFront();
	s.PopFront();
	s.PopFront();
	s.PopFront();
	s.PopFront();
	s.Print();*/

	//DoubleList s1(s);
	//s1.Print();

	DoubleList s2;
	s2.PushBack(9);
	s2.PushBack(8);
	s2.PushBack(7);
	s2.PushBack(6);
	s2.Print();

	s = s2;
	s.Print();

	//s.Reverse();
	s.Print();
}
int main()
{

	Test();
	system("pause");
	return 0;
}
