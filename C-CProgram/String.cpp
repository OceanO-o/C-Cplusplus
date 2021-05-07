#pragma once
#include<iostream>
#pragma warning(disable:4996)
//#include<assert.h>
using namespace std;

class String
{
public:
	String() //Ĭ�Ϲ��캯��
		:_str(new char[1])   //Ҫnew[]������new����Ϊdeleteʱ�õ�delete[]
	{
		//str = ""; //ǧ���������ã���Ϊ�����Ǹ�str��ֵ����strָ�����γ�������������deleteʱ��
		//                   //delete���Ƕ��ϵĿռ䣬��ʱ��delete����οռ䣬��������
		//_str[0] = '\0';    //���Ҳ����
		//*_str = 0;        //��ò�Ҫ������
		*_str = '\0';
	}
	String(char* str)
		:_str(new char [strlen(str) + 1])     //:_str(str)//Ϊʲô�������������Ļ� s->_str�ʹ���
	{	                                     // ����Σ����������ܱ��ı䣬����ı�Ͳ��С�
		strcpy(_str, str);
	}
	String(const String& s)
	{
		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
	}
	//String(const String& s)  //����һ�ֿ�������
	//{                               ��_str = NULL;
	//	_str = new char[1];   //   ����ֱ�Ӱ�  _str = NULL,�Ͳ��������
	//	String tmp(s._str);//���ù��캯����ʼ��
	//	swap(tmp.str, this.str);
	//}
	String& operator = (const String& s)
	{
		if (this != &s)//ΪʲôҪ���������Լ����Լ���ֵʱ����delete _str��strlen��str��ûֵ
		{	                         //����strcpyֵΪ���ֵ��
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
	//		String tmp(s._str);//��һ��������������ͷ�tmp���൱�������Ǹ�����������ֵ��delete����
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
//	//const������Ե��÷�const��Ա������const��Ա������
//	//��const������Ե��÷�const��Ա������const��Ա������
//	//const��Ա�����ڿ��Ե���������const��Ա������const��Ա������
//	//��const��Ա�����ڿ��Ե���������const��Ա������const��Ա������
//}

int main()
{
	Test();
	system("pause");
	return 0;
}