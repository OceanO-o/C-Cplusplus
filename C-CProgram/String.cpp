#pragma once
#include<iostream>
#pragma warning(disable:4996)
//#include<assert.h>
using namespace std;

class String
{
public:
	String() //默认构造函数
		:_str(new char[1])   //要new[]而不是new，因为delete时用的delete[]
	{
		//str = ""; //千万不能这样用，因为这样是给str赋值，让str指向代码段常量区，而当你delete时，
		//                   //delete的是堆上的空间，此时你delete代码段空间，程序会崩溃
		//_str[0] = '\0';    //这个也可以
		//*_str = 0;        //最好不要这样用
		*_str = '\0';
	}
	String(char* str)
		:_str(new char [strlen(str) + 1])     //:_str(str)//为什么不这样，这样的话 s->_str就存在
	{	                                     // 代码段，常量区不能被改变，若想改变就不行。
		strcpy(_str, str);
	}
	String(const String& s)
	{
		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
	}
	//String(const String& s)  //另外一种拷贝构造
	//{                               ：_str = NULL;
	//	_str = new char[1];   //   可以直接把  _str = NULL,就不用这句了
	//	String tmp(s._str);//调用构造函数初始化
	//	swap(tmp.str, this.str);
	//}
	String& operator = (const String& s)
	{
		if (this != &s)//为什么要这样，当自己给自己赋值时，当delete _str后，strlen（str）没值
		{	                         //而且strcpy值为随机值。
			delete _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
		}
		return *this;
	}
	//String& operator = (const String& s)
	//{
	//	if (this != &s)
	//	{
	//		String tmp(s._str);//这一步出了作用域会释放tmp，相当于上面那个的两步（赋值和delete）。
	//		swap(s._str, _str);
	//	}
	//	return *this;
	//}
	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = NULL;
		}
	}


	bool operator >(const String& s)
	{
		const char* str1 = _str;
		const char* str2 = s._str;

		while(*str1 && *str2)
		{
			if (*str1 > *str2)
				return true;
			else if (*str1 < *str2)
				return false;
			else
			{
				str1++;
				str2++;
			}
		}

		if (*str1)
			return true;
		return false;
	}
	bool operator <(const String& s)
	{
		return !(*this>s);
	}
	bool operator == (const String& s)
	{
		const char* str1 = _str;
		const char* str2 = s._str;

		while (*str1 && str2)
		{
			if (*str1 == *str2)
			{
				++str1;
				++str2;
			}
			else
				return false;
		}
		if (*str1 || *str2)
		{
			return false;
		}
		return true;
	}
	bool operator >= (const String& s)
	{
		return ((*this > s) || (*this == s));
	}
	bool operator <= (const String& s)
	{
		return ((*this < s) || (*this == s));
	}


private:
	char* _str;
};

void Test()
{
	String s1("hello world");
	String s2(s1);
	String s3("helloge world");
	//s3 = s2;
	//s3(s1);
	int len;
	len = s3 > s2;

	String s4("imissyou");
	String s5("imissyoutoo");

	len = (s4 == s5);
}
//void Test()
//{
//	Date d1;
//	d1.Display();     //void Display()
//
//	const Date d2;    //void Display() const
//	d2.Display();
//	//const对象可以调用非const成员函数和const成员函数吗？
//	//非const对象可以调用非const成员函数和const成员函数吗？
//	//const成员函数内可以调用其它的const成员函数非const成员函数吗？
//	//非const成员函数内可以调用其它的const成员函数非const成员函数吗？
//}

int main()
{
	Test();
	system("pause");
	return 0;
}