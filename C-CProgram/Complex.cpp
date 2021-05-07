#pragma once
#include<iostream>

using namespace std;

class Complex
{
public:
	Complex(double real = 0, double imag =0)
		:_real(real)
		,_imag(imag)
		{}
	
	Complex(const Complex &c)
	{
		if (this != &c )
		{
			this->_real = c._real;
			this->_imag = c._imag;
		}
	}

	~Complex()
	{

	}
	Complex& operator = (const Complex& c)
	{
		if (this != &c)
		{
			this->_real = c._real;
			this->_imag = c._imag;
		}
		return *this;
	}

	bool operator>(const Complex& c)
	{
		if ((this->_imag == c._imag))
		{
			if (this->_real > c._real)
				return true;
		}
		return false;
	}
	bool operator<(const Complex& c)
	{
		if ((this->_imag == c._imag))//(this->_imag ==/&& c._imag) == 0
		{
			if (this->_real < c._real)
				return true;
		}
		return false;
	}

	bool operator==(const Complex& c)
	{	
		if (this->_real == c._real)
		{
			if (this->_imag == c._imag)
				return true;
		}
		return false;
	}
	
	Complex operator+(const Complex& c)
	{
		Complex tmp;
		tmp._real = this->_real + c._real;
		tmp._imag = this->_imag + c._imag;
		return tmp;
	}

	Complex& operator += (const Complex& c)
	{
		this->_real = this->_real + c._real;
		this->_imag = this->_imag + c._imag;
		return *this;
	}

	Complex operator -(const Complex& c)
	{
		Complex tmp;
		tmp._real = this->_real - c._real;
		tmp._imag = this->_imag - c._imag;
		return tmp;
	}
	Complex& operator -= (const Complex& c)
	{
		this->_real = this->_real - c._real;
		this->_imag = this->_imag - c._imag;
		return *this;
	}
	Complex& operator++()
	{
		++this->_real;
		++this->_imag;
		return *this;
	}
	Complex operator++(int)
	{
		Complex tmp(*this);
		this->_real++;
		this->_imag++;
		return tmp;
	}

private:
	double _real;
	double _imag;	
};
#pragma once
#include "complex.h"

void test1()
{
	Complex c1(5, 1);
	Complex c2(3, 7.6);
	//Complex c3 = c2;  //如果对象没赋值，则调用拷贝构造。
	//c2 = c1;         //这种对象已赋值，则调用的是赋值运算符重载。
	//Complex c3(c2);  //拷贝构造

	/*int flag1, flag2;
	flag1 = c1 == c2;
	flag2 = c1 < c2;
	cout << flag1 << " " << flag2 << endl;*/

	//Complex c3 = c1 + c2;
	 //c1 += c2;
	//Complex c3 = c1 - c2;
	 //c1 -= c2;
	Complex ret;
	ret = c2++;
	ret = ++c1;
}
int main()
{
	//test();
	test1();
	system("pause");
	return 0;
}