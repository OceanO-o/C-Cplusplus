#include<iostream>
using namespace std;



//int main()
//{
//	union
//	{
//		int x;
//		char ch[2];
//	}a;
//	a.ch[0] = 0x39;
//	a.ch[1] = 0x38;
//	printf("%d\n", a.x);
//	system("pause");
//	return 0;           //这样不行，答案出错
//}
union
{
	int i;
	char a[2];
}u; 
int main()
{
	
	u.a[0] = 0x39;     //小端模式   3     8     3     9    
	u.a[1] = 0x38;     //           0011  1000  0011  1001
	printf("i = %d\n", u.i);      //14393
	system("pause");
	return 0;
}



//bool check()
//{
//	union
//	{                   //共用体，变量存储地址具有相同的起始位置，所以i的存储状态如下
//		int i;          //     0x 00 00 00 01             0x 00 00 00 00 01
//		char a;        //         ---->高地址                   高地址<----
//	}u;                //   a和i具有相同存储地址，总是起始地址进去。所以a可能取到 0 也可能取到 1
//	                   //  a如果取到0，则说明1在高地址（大端），a如果取到1，则说明a在低地址（小端）
//	u.i = 1;           //
//	printf("%d", u.a);
//	return 0;
//}
//int main()
//{
//	check();
//	system("pause");
//	return 0;
//}
