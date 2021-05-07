//#pragma once
//#include<iostream>
//#include<vector>
//using namespace std;

//template<class T,class Container = vector<T>>
//class Queue
//{
//public:
//	void PushBack(const T& x)
//	{
//		con.push_back(x);
//	}
//private:
//	Container con;
//};
//
//void Test()
//{
//	Queue<int, vector<int>> q1;
//	q1.PushBack(1);
//}

//template<class T, template <class> class Container  >
//class Queue
//{
//public:
//	void PushBack(const T& x)
//	{
//		con.push_back(x);
//	}
//private:
//	Container<T> con;
//};
//
//void Test()
//{
//	Queue<int, vector> q1;
//	q1.PushBack(1);
//	q1.PushBack(2);
//	q1.PushBack(3);
//	q1.PushBack(4);
//
//}

#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

template <class T>
struct ListNode
{
	T _data;
	ListNode<T>* _next;
	ListNode(const T& x)
		:_data(x)
		, _next(NULL)	
	{}
};
template <class T>
class Queue
{
public:
	Queue()
	:_head(NULL)
	, _tail(NULL)
	{}
	
	~Queue()
	{
		ListNode<T>* tmp = _head;
		while (tmp)
		{
			ListNode<T>* cur = tmp;	
			tmp = tmp->_next;
			delete cur;
		}
	}

	void Push( const T& x) // push_front
	{
		if (_head == NULL)
		{
			_head = _tail = new ListNode<T>(x);
		}
		else
		{
			ListNode<T>* tmp = new ListNode<T>(x);
			_tail->_next = tmp;
			_tail = _tail->_next;
		}
	}

	void Pop()
	{
		assert(_head);//if (_head == NULL)节点为空
		if (_head == _tail)//一个节点
		{
			delete _head;
			_head = _tail = NULL;
			return;
		}
		else
		{
			ListNode<T>* tmp = _head;//头删（先进先出）
			_head = _head->_next;
			delete tmp;
		}
	}

	void Print()
	{
		ListNode<T>* tmp = _head;
		cout << "队头";
		while (tmp)
		{
			cout << tmp->_data << "->";
			tmp = tmp->_next;
		}
		cout << "队尾" << endl;
	}

	bool Empty()
	{
		return (_head == NULL);
	}

	T& Front()
	{
		return _head->_data;
	}

	T& Tail()
	{
		return _tail->_data;
	}
private:
	ListNode<T>* _head;
	ListNode<T>* _tail;
};

void Test()
{
	Queue<int> q1;
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	q1.Push(4);
	q1.Push(5);

	q1.Print();

	q1.Pop();
	q1.Print();



	cout << "头->" << q1.Front() << "尾->" << q1.Tail() << endl;
}

